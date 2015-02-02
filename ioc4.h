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

#define CALLTRACE cout << __PRETTY_FUNCTION__  << " called" << endl;


using namespace epics::pvData;
using namespace epics::pvDatabase;
using namespace epics::pvAccess;

using namespace std::tr1;
using namespace std;

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

    inline PVRecordFieldPtr findPVRecordFieldByName(string field){
        PVFieldPtr data = getPVStructure()->getSubField(field);

        if(!data) throw runtime_error(("Field "+field+" does not exist in record " + getRecordName()));

        PVRecordFieldPtr fieldPtr = findPVRecordField(data);
        return fieldPtr;
    }

    inline PVFieldPtr findPVFieldByName(string fieldName){
        return getPVStructure()->getSubField(fieldName);
    }


    void addFieldHandler(PVRecordFieldPtr field ,function<void(PVRecordFieldPtr const)> listner);





};

#include "pvutils.h"
class ioc4{
public:
    void addFactory(string name, function<iocRecordPtr(string,PVStructurePtr)> createRecord, function<StructureConstPtr(void)> getForm){
        recordFactories[name]=createRecord;
        formFactories[name]=getForm;
    }



    iocRecordPtr initRecord(string type, string name);
    PVStructurePtr createRecord(string type, string name);

    PVStructurePtr createRecord(string name, StructureConstPtr def);

    iocRecordPtr findRecord(string name){
        PVDatabasePtr db = PVDatabase::getMaster();
        PVRecordPtr record = db->findRecord(name);
        return dynamic_pointer_cast<iocRecord>(record);
    }

    PVRecordFieldPtr findField(string name);

    void setField(string name, string value);

    void setStagingField(string name, string value);

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

    // Factories
    map<string,function<iocRecordPtr(string,PVStructurePtr)>> recordFactories;
    map<string,function<StructureConstPtr(void)>> formFactories;


};




#endif
