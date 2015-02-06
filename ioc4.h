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

//#define CALLTRACE cout << __PRETTY_FUNCTION__  << " called" << endl;
#define CALLTRACE


using namespace epics::pvData;
using namespace epics::pvDatabase;
using namespace epics::pvAccess;

using namespace std::tr1;
using namespace std;


class iocPutLink;
typedef std::tr1::shared_ptr<iocPutLink> iocPutLinkPtr;

class iocPutLink{
public:
    PVRecordFieldPtr src, dest;
//    PVTimeStamp destTimestamp;
//    TimeStamp t;

    iocPutLink(PVRecordFieldPtr src, PVRecordFieldPtr dest);
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


};



#include "pvutils.h"
class ioc4{
public:
    void addFactory(string name, function<iocRecordPtr(string,PVStructurePtr)> createRecord, function<StructureConstPtr(void)> getForm){
        recordFactories[name]=createRecord;
        formFactories[name]=getForm;
    }



    /**Record creation **/
    iocRecordPtr initRecord(string type, string name);
    PVStructurePtr createRecord(string type, string name);
    PVStructurePtr createRecord(string name, StructureConstPtr def);

    /**Record and field find utilities **/
    iocRecordPtr findRecord(string name);
    PVRecordFieldPtr findField(string name);

    /**Field modifications **/
    void setField(string name, string value);
    void setStagingField(string name, string value);

    /**Link creation **/
    void addLink(string from,string to,string specifications);

    void startPVAccess();
    void stopPVAccess();


    /**
     * @brief getIoc singleton...
     * @return
     */
    static ioc4* getIoc();



private:

    //Staging database
    map<string,PVStructurePtr> stagingDb;

    //Links
    vector<iocPutLinkPtr> putLinks;

    // Factories
    map<string,function<iocRecordPtr(string,PVStructurePtr)>> recordFactories;
    map<string,function<StructureConstPtr(void)>> formFactories;


};




#endif
