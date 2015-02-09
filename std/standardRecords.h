#include "../ioc4.h"
#include "luaRecord.h"
#include "ioc4gtp.h"


class ScanRecord{
public:
    /**
     * @brief getForm
     *
     * This function is registered to record factory and is invoked whenever a record with that name is created
     *
     * @return
     */
    static StructureConstPtr getForm(){
        return getFieldCreate()->createFieldBuilder()->
                add("value",pvUInt)->
                add("rate",pvDouble)->
                add("timestamp",getStandardField()->timeStamp())->
                createStructure();
    }

    /**
     * @brief bind
     *
     * Bind the record logic to given record.
     *
     * In this method you should check for existance of fields and set the default values.
     *
     * @param name
     * @param record
     */
    static void bind(iocRecordPtr record){
        //Confirm that all of the fields exist
        //This has to be done here so that the constructor doesnt fail
        PVUIntPtr value = dynamic_pointer_cast<PVUInt>(record->findPVField("value"));
        PVStructurePtr timestamp = dynamic_pointer_cast<PVStructure>(record->findPVField("timestamp"));


        if(!value){
            throw runtime_error(("Record "+record->getRecordName()+" does not have field value"));
        }


        if(!timestamp){
            throw runtime_error("Record "+record->getRecordName()+" does not have field timestamp");
        }

        new ScanRecord(record);
    }

private:
    iocRecordPtr    m_record;

    PVUIntPtr       m_value;
    PVDoublePtr     m_rate;
    PVStructurePtr  m_timestamp;

    ScanRecord(iocRecordPtr record){
        //Store pointers to all of the fields so that we do not have to look for them every time...
        m_record = record;
        m_value = dynamic_pointer_cast<PVUInt>(record->findPVField("value"));
        m_rate = dynamic_pointer_cast<PVDouble>(record->findPVField("rate"));
        m_timestamp = dynamic_pointer_cast<PVStructure>(record->findPVField("timestamp"));

        //Start the thread
        string thread_name = m_record->getRecordName()+":SCAN";
        epicsThreadCreate(thread_name.c_str(),epicsThreadPriorityMedium,epicsThreadStackMedium,&ScanRecord::scanThread,this);
    }

    static void scanThread(void* param){
        ScanRecord* s = static_cast<ScanRecord*>(param);

        cout << "Starting the scan theread for record "+s->m_record->getRecordName() << endl;

        while(1){
            //Increase m_value counter by 1
            s->m_value->put(s->m_value->get()+1);
            epicsThreadSleep(s->m_rate->get());
        }
    }
};

class StandardRecords{
public:
    static void registerStandardRecords(){
        ioc4* ioc = ioc4::getIoc();

        //Register basic record types
        ioc->addRecordFactory("INT",[&](){
            return getFieldCreate()->createFieldBuilder()->add("value",pvInt)->add("timestamp",getStandardField()->timeStamp())->createStructure();
        });

        ioc->addRecordFactory("UINT",[&](){
            return getFieldCreate()->createFieldBuilder()->add("value",pvUInt)->add("timestamp",getStandardField()->timeStamp())->createStructure();
        });

        ioc->addRecordFactory("DOUBLE",[&](){
            return getFieldCreate()->createFieldBuilder()->add("value",pvDouble)->add("timestamp",getStandardField()->timeStamp())->createStructure();
        });

        ioc->addRecordFactory("STRING",[&](){
            return getFieldCreate()->createFieldBuilder()->add("value",pvString)->add("timestamp",getStandardField()->timeStamp())->createStructure();
        });



        ioc->addRecordFactory("STD::SCAN",&ScanRecord::getForm);

        //Register standard components
        ioc->addComponentFacotry("STD::SCAN",&ScanRecord::bind);
        ioc->addComponentFacotry("STD::LUA",&LuaRecord::init);

        //Register gtp
        register_ioc4gtp();

    }
};
