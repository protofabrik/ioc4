#ifndef IOC4_H_DEF
#define IOC4_H_DEF

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

#include "simplesignal.h"



//#define CALLTRACE cout << __PRETTY_FUNCTION__  << " called" << endl;
#define CALLTRACE


using namespace epics::pvData;
using namespace epics::pvDatabase;
using namespace epics::pvAccess;

using namespace std::tr1;
using namespace std;

using namespace Simple;


class iocPutLink;
typedef std::tr1::shared_ptr<iocPutLink> iocPutLinkPtr;

class iocPutLink:public PVListener{
public:
    PVRecordFieldPtr src, dest;
    PVFieldPtr srcData, destData;
    ConvertPtr convert;

    iocPutLink(PVRecordFieldPtr src, PVRecordFieldPtr dest);

    void dataPut(PVRecordFieldPtr const & pvRecordField){
        this->dest->getPVRecord()->lock();
        this->convert->copy(this->srcData,this->destData);
        this->dest->getPVRecord()->unlock();

    }

    void dataPut(
            PVRecordStructurePtr const & requested,
            PVRecordFieldPtr const & pvRecordField){

    }



    virtual void beginGroupPut(PVRecordPtr const & pvRecord){}

    virtual void endGroupPut(PVRecordPtr const & pvRecord){}

    virtual void unlisten(PVRecordPtr const & pvRecord){}

    virtual void detach(PVRecordPtr const & pvRecord){}
};


class iocRecord;
typedef std::tr1::shared_ptr<iocRecord> iocRecordPtr;
class iocRecord : public PVRecord{
public:

    PVStructurePtr const data;

    static iocRecord* constructRecord(string name);


    iocRecord(string name,PVStructurePtr pvStruct):
        PVRecord(name,pvStruct),
        data(pvStruct){
    }

    virtual bool init(){
        PVRecord::init();
    }

    PVRecordFieldPtr findPVRecordFieldByName(string field);

    void addFieldHandler(PVRecordFieldPtr field ,function<void(PVRecordFieldPtr const)> listner);

    PVFieldPtr findPVField(string field);

};

class iocCmd{
public:
    string getStringArg(PVStructurePtr args, string name, string defult_val){
        PVFieldPtr field = args->getSubField(name);

        if(field->getField()->getType()==scalar){
//            getConvert()->toString();
        }
    }
};


#include "pvutils.h"
class ioc4{
public:
    void addRecordFactory(string name, function<StructureConstPtr(void)> getForm){
        recordFactories[name]=getForm;
    }

    void addComponentFacotry(string name, function<void(iocRecordPtr)> init){
        componentFactories[name]=init;
    }

    void addCmd(string name, function<PVStructurePtr(PVStructurePtr)> function){
        commands[name]=function;
    }

    /**Record creation **/
    iocRecordPtr initRecord(string name);
    iocRecordPtr bindRecord(string name, string component);
    PVStructurePtr createRecord(string name, string type);
    PVStructurePtr createRecord(string name, StructureConstPtr def);

    /**Record and field find utilities **/
    iocRecordPtr findRecord(string name);
    PVRecordFieldPtr findField(string name);

    /**Field modifications **/
    void setField(string name, string value);
    void setStagingField(string name, string value);
    void addStagingField(string name, string type);


    /**Link creation **/
    void addLink(string from,string to,string specifications);

    void startPVAccess();
    void stopPVAccess();


    /** Commands **/

    static PVStructurePtr addLinkCmd(PVStructurePtr args){
        //Extract arguments
        PVStringPtr from,to,type,param;

        from=args->getStringField("from");
        to=args->getStringField("to");
        type=args->getStringField("type");
        param=args->getStringField("param");

        //Throw error if arguments are missing
        if(!(from&&to&&type&&param)) throw runtime_error("Not all arguments present");

        //Invoke
        ioc4::getIoc()->addLink(from->get(),to->get(),"");

        //Nothing to return
        return PVStructurePtr();
    }

    /**
     * @brief getIoc singleton...
     * @return
     */
    static ioc4* getIoc();

    Signal<void(iocRecordPtr)>sig_recordInDatabase;
    Signal<void(PVStructurePtr)>sig_recordInStaging;
    Signal<void(PVStructurePtr&)>sig_recordAfterStaging;


private:

    //Staging database
    map<string,PVStructurePtr> stagingDb;

    //Links
    vector<iocPutLinkPtr> putLinks;

    // Factories
//    map<string,function<iocRecordPtr(string,PVStructurePtr)>> recordFactories;
    map<string,function<StructureConstPtr(void)>> recordFactories;
    map<string,function<void(iocRecordPtr)>> componentFactories;

    // Commands
    map<string,function<PVStructurePtr(PVStructurePtr)>> commands;


};


class ioc4s{
public:
    static void init(){
        std::cout << "Intializing IOC" << endl;
        ioc4* ioc = ioc4::getIoc();
//        StandardRecords::registerStandardRecords();
    }

    static void createRecord(string name, string type){
        ioc4::getIoc()->createRecord(name,type);
    }

    static void setStagingField(string name, string val){
        ioc4::getIoc()->setStagingField(name,val);
    }

    static void addStagingField(string name, string type){
        ioc4::getIoc()->addStagingField(name,type);
    }

    static void bindRecord(string name, string type){
        ioc4::getIoc()->bindRecord(name,type);
    }

    static void initRecord(string name){
        ioc4::getIoc()->initRecord(name);
    }

    static void addLink(string from, string to,string type, string args){
        ioc4::getIoc()->addLink(from,to,args);
    }

    static void startPVA(){
        ioc4::getIoc()->startPVAccess();
    }

    static vector<string> dbl(){
        PVStringArray::const_svector records;

        PVDatabase::getMaster()->getRecordNames()->getAs(records);

        vector<string> output;
        for(string name : records){
            output.push_back(name);
        }

        return output;
    }

};





#endif

