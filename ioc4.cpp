#include <stdlib.h>
#include <stdio.h>
#include <functional>



#include <pv/pvData.h>
#include <pv/pvAccess.h>
#include <pv/convert.h>
#include <pv/standardField.h>
#include <pv/standardPVField.h>
#include <pv/channelProviderLocal.h>
#include <pv/serverContext.h>


#include <pv/pvDatabase.h>

#include "ioc4.h"




class iocRecordListner;
typedef std::tr1::shared_ptr<iocRecordListner> iocRecordListnerPtr;


typedef function<void(PVRecordFieldPtr const)> listner_t;


class iocRecordListner : public PVListener{
public:

    iocRecordListner(listner_t l):listner(l),inProcess(false){CALLTRACE}
private:

    bool inProcess;
    listner_t listner;



    void dataPut(PVRecordFieldPtr const & pvRecordField){
        CALLTRACE
                if(inProcess) return;
        inProcess=true;
        listner(pvRecordField);
        inProcess=false;
    }

    void dataPut(
            PVRecordStructurePtr const & requested,
            PVRecordFieldPtr const & pvRecordField){
        CALLTRACE
                inProcess=true;
        listner(pvRecordField);
        inProcess=false;
    }



    virtual void beginGroupPut(PVRecordPtr const & pvRecord){
        CALLTRACE
    }

    virtual void endGroupPut(PVRecordPtr const & pvRecord){CALLTRACE}

    virtual void unlisten(PVRecordPtr const & pvRecord){CALLTRACE}

    virtual void detach(PVRecordPtr const & pvRecord){CALLTRACE}

};




iocRecord *iocRecord::constructRecord(string name){
    FieldCreatePtr fieldCreate = getFieldCreate();
    StandardFieldPtr standardField = getStandardField();
    PVDataCreatePtr dataCreate = getPVDataCreate();

    StructureConstPtr recordForm =  fieldCreate->createFieldBuilder()->
            add("value",pvDouble)->
            add("timestamp",standardField->timeStamp())->
            createStructure();

    return new iocRecord(name,dataCreate->createPVStructure(recordForm));
}

void iocRecord::addFieldHandler(PVRecordFieldPtr field, function<void (const PVRecordFieldPtr)> listner){
    CALLTRACE
            //        assert(field);

            PVListenerPtr l(new iocRecordListner(listner));

    //    this->addListener(l);
    field->addListener(l);
    //        findPVRecordField(field)->postPut();
}


iocRecordPtr ioc4::initRecord(string type, string name)
{

    if(!stagingDb.count(name)) throw runtime_error("Record "+name+" does not exist in stageing database");

    PVStructurePtr recordData = stagingDb[name];
    stagingDb.erase(name);


    if(type == ""){
        iocRecordPtr record( new iocRecord(name,recordData) ) ;
        PVDatabase::getMaster()->addRecord(record);
        record->init();
        return record;
    }


    if(!recordFactories.count(type)) throw runtime_error("Record type: "+type+" does not exist!\n");

    iocRecordPtr record = recordFactories[type](name,recordData);
    record->init();
    PVDatabase::getMaster()->addRecord(record);
    return record;

}

PVStructurePtr ioc4::createRecord(string type, string name){
    if(formFactories.count(type)){
        StructureConstPtr form = formFactories[type]();

        PVStructurePtr data = getPVDataCreate()->createPVStructure(form);

        stagingDb[name]=data;

        return data;
    }
    else{
        throw runtime_error("Record type: "+type+" does not exist!\n");
    }

}

PVStructurePtr ioc4::createRecord(string name, StructureConstPtr form){
    PVStructurePtr data = getPVDataCreate()->createPVStructure(form);

    stagingDb[name]=data;

    return data;
}

iocRecordPtr ioc4::findRecord(string name){
    PVDatabasePtr db = PVDatabase::getMaster();
    PVRecordPtr record = db->findRecord(name);
    return dynamic_pointer_cast<iocRecord>(record);
}

PVRecordFieldPtr ioc4::findField(string name){

    //Split the name into record and fields
    size_t index = name.find(".",0);
    string recordName = name.substr(0,index);
    string fieldName = name.substr(index+1);

    iocRecordPtr record = findRecord(recordName);
    if(!record)
        throw runtime_error(("Record "+recordName+" does not exist!"));



    return record->findPVRecordFieldByName(fieldName);
}

void ioc4::setField(string name, string value){
    PVRecordFieldPtr recordField = findField(name);
    StringArray arr;

    std::stringstream ss(value);
    std::string item;
    while (std::getline(ss, item, ' ')) {
        arr.push_back(item);
    }


    PVFieldPtr field = recordField->getPVField();
    fromString(field,arr,0);
}

void ioc4::setStagingField(string name, string value){
    //Split the name into record and fields
    size_t index = name.find(".",0);
    string recordName = name.substr(0,index);
    string fieldName = name.substr(index+1);

    if(!stagingDb.count(recordName)) throw runtime_error(("Staging record "+recordName+" does not exist!"));

    PVStructurePtr record = stagingDb[recordName];

    //Check if field exists
    PVFieldPtr field = record->getSubField(fieldName);

    //TODO add creation of optional fields
    if(!field){

        //        throw runtime_error(("Staging record "+recordName+" does not have a required field "+fieldName));

        //Create new form with addtional field
        StructureConstPtr newForm = getFieldCreate()->appendField(record->getStructure(),fieldName,getFieldCreate()->createScalar(pvString));
        //Create new data from the form
        PVStructurePtr newRecord = getPVDataCreate()->createPVStructure(newForm);
        //Copy existing data to new record
        for(PVFieldPtr a : record->getPVFields()){
            getConvert()->copy(a,newRecord->getSubField(a->getFieldName()));

        }

        stagingDb[recordName]=newRecord;
        record=newRecord;

        field = newRecord->getSubField(fieldName);
    }

    //Copy value
    StringArray arr;
    std::stringstream ss(value);
    std::string item;
    while (std::getline(ss, item, ' ')) {
        arr.push_back(item);
    }

    fromString(field,arr,0);
}

void ioc4::addLink(string from, string to, string specifications)
{
    PVRecordFieldPtr fromField = findField(from);
    PVRecordFieldPtr toField = findField(to);

    iocPutLinkPtr link (new iocPutLink(fromField,toField) );
    putLinks.push_back(link);
}

void ioc4::startPVAccess(){
    /** pvDatabase init **/
    ChannelProviderLocalPtr channelProvider = getChannelProviderLocal();    

    ServerContext::shared_pointer pvaServer =
            startPVAServer(PVACCESS_ALL_PROVIDERS,0,true,true);
    cout << "STARTED pvDatabase" << endl;

}

void ioc4::stopPVAccess(){
    //    pvaServer->shutdown();
    //    epicsThreadSleep(1.0);
    //    pvaServer->destroy();
    //    channelProvider->destroy();
}


ioc4 *ioc4::getIoc(){
    static ioc4 instance;
    return &instance;
}


iocPutLink::iocPutLink(PVRecordFieldPtr src, PVRecordFieldPtr dest):src(src),dest(dest){
    assert(src.get());
    assert(dest.get());

    //Get source record
    iocRecordPtr srcRecord = dynamic_pointer_cast<iocRecord>(src->getPVRecord());

    PVFieldPtr srcData = src->getPVField();
    PVFieldPtr destData = dest->getPVField();

    //Check if we can copy
    if(!getConvert()->isCopyCompatible(srcData->getField(),destData->getField()))
        throw runtime_error(("Can not create PUT link since field"+
                             src->getFullName()+
                             " and "+dest->getFullName()+
                             " are not copy compatible"));


    srcRecord->addFieldHandler(src,[this](PVRecordFieldPtr const arg){
        getConvert()->copy(this->src->getPVField(),this->dest->getPVField());
    });
}


PVRecordFieldPtr iocRecord::findPVRecordFieldByName(string field){

    PVFieldPtr data = this->data;

    //Iterate over fields
    std::stringstream ss(field);
    std::string subFieldName;
    while (std::getline(ss, subFieldName, '.')) {
        PVStructurePtr dataStruct = dynamic_pointer_cast<PVStructure>(data);
        if(!dataStruct) throw runtime_error(("Field "+field+" does not exist in record " + getRecordName()));

        data = dataStruct->getSubField(subFieldName);
        if(!data) throw runtime_error(("Field "+field+" does not exist in record " + getRecordName()));
    }

    if(!data) throw runtime_error(("Field "+field+" does not exist in record " + getRecordName()));



    PVRecordFieldPtr fieldPtr = findPVRecordField(data);
    return fieldPtr;
}
