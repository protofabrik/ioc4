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


iocRecordPtr ioc4::initRecord(string name)
{
    //Check if record is already initialized
    iocRecordPtr r = dynamic_pointer_cast<iocRecord>(PVDatabase::getMaster()->findRecord(name));
    if(r) return r;


    //Check if record exists in staging database
    if(!stagingDb.count(name)) throw runtime_error("Record "+name+" does not exist in staging database");

    //Init record and put it into pvDatabase
    PVStructurePtr recordData = stagingDb[name];
    stagingDb.erase(name);

    sig_recordAfterStaging.emit(recordData);

    iocRecordPtr record( new iocRecord(name,recordData) ) ;
    PVDatabase::getMaster()->addRecord(record);
    record->init();
    sig_recordInDatabase.emit(record);
    return record;
}

iocRecordPtr ioc4::bindRecord(string name, string component)
{
    if(!componentFactories.count(component)){
        throw runtime_error("Component "+component+" does not exist!");
    }

    iocRecordPtr record = initRecord(name);
    componentFactories[component](record);

    return record;
}

PVStructurePtr ioc4::createRecord(string name, string type){
    if(recordFactories.count(type)){
        StructureConstPtr form = recordFactories[type]();

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

    //If field is string copy literal
    PVStringPtr strField = dynamic_pointer_cast<PVString>(field);
    if(strField){
        strField->put(value);
        return;
    }

    //else use from string
    StringArray arr;
    std::stringstream ss(value);
    std::string item;
    while (std::getline(ss, item, ',')) {
        arr.push_back(item);
    }

    fromString(field,arr,0);
}

void ioc4::addStagingField(string name, string type)
{
    size_t index = name.find(".",0);
    string recordName = name.substr(0,index);
    string fieldName = name.substr(index+1);

    if(!stagingDb.count(recordName)) throw runtime_error(("Staging record "+recordName+" does not exist!"));

    PVStructurePtr record = stagingDb[recordName];

    //Check if field exists
    PVFieldPtr field = record->getSubField(fieldName);

    //TODO add creation of optional fields
    if(!field){

        //Create new form with addtional field
        ScalarConstPtr scalar;
        if(type=="string")
            scalar = getFieldCreate()->createScalar(pvString);
        else if(type=="int")
            scalar = getFieldCreate()->createScalar(pvInt);
        else if(type=="double")
            scalar = getFieldCreate()->createScalar(pvDouble);
        else if(type=="uint")
            scalar = getFieldCreate()->createScalar(pvUInt);
        else
            throw runtime_error("Unknown field type "+type);

        StructureConstPtr newForm = getFieldCreate()->appendField(record->getStructure(),fieldName,scalar);
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

}

void ioc4::addLink(string from, string to, string type, string specifications)
{
    PVRecordFieldPtr fromField = findField(from);
    PVRecordFieldPtr toField = findField(to);

    if(type=="PUT")
        (new iocPutLink(fromField,toField) );
    else if(type=="COPY")
        (new iocCopyLink(fromField,toField) );

    //    putLinks.push_back(link);
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

#include <lttng/tracef.h>



/**
 * @brief iocRecord::findPVRecordFieldByName
 *
 * DEPRECATED, use findPVField and findPVRecordField
 *
 * @param field
 * @return
 */
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


PVFieldPtr iocRecord::findPVField(string field){
    PVFieldPtr data = getPVStructure();

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

    return data;
}




iocPutLink::iocPutLink(PVRecordFieldPtr src, PVRecordFieldPtr dest):src(src),dest(dest){
    //Get source record
    iocRecordPtr srcRecord = dynamic_pointer_cast<iocRecord>(src->getPVRecord());

    srcData = src->getPVField();
    destData = dest->getPVField();
    convert = getConvert();

    //        //Check if we can copy
    //        if(!convert->isCopyCompatible(srcData->getField(),destData->getField()))
    //            throw runtime_error(("Can not create PUT link since field"+
    //                                 src->getFullName()+
    //                                 " and "+dest->getFullName()+
    //                                 " are not copy compatible"));

    if(!copy.addCopy(srcData,destData))
        throw runtime_error(("Can not create PUT link since field"+
                             src->getFullName()+
                             " and "+dest->getFullName()+
                             " are not put compatible, consider using COPY link instead"));

    src->addListener(iocPutLinkPtr(this));
}


iocCopyLink::iocCopyLink(PVRecordFieldPtr src, PVRecordFieldPtr dest):src(src),dest(dest)
{

    //Get source record
    iocRecordPtr srcRecord = dynamic_pointer_cast<iocRecord>(src->getPVRecord());

    srcData = src->getPVField();
    destData = dest->getPVField();
    convert = getConvert();

    //Check if we can copy
    if(!convert->isCopyCompatible(srcData->getField(),destData->getField()))
        throw runtime_error(("Can not create COPY link since field"+
                             src->getFullName()+
                             " and "+dest->getFullName()+
                             " are not copy compatible"));

    iocCopyLinkPtr ptr(this);
    src->addListener(ptr);
}
