
#include <pv/pvTimeStamp.h>
#include "ioc4.h"


class ioc4PutLink{
public:
    PVRecordFieldPtr src, dest;
    PVTimeStamp destTimestamp;
    TimeStamp t;

    ioc4PutLink(PVRecordFieldPtr src, PVRecordFieldPtr dest):src(src),dest(dest){
        assert(src.get());
        assert(dest.get());

        //Get source record
        iocRecordPtr srcRecord = dynamic_pointer_cast<iocRecord>(src->getPVRecord());


        //Check if dest is structure
//        if(destTimestamp.attach(dest->getParent()->getPVStructure()->getSubField("timestamp"))){
//               cout <<"VALID TIMESTAMP"<<endl;
//         }


        srcRecord->addFieldHandler(src,[this](PVRecordFieldPtr const arg){
            cout << "PUT LINK!" << endl;
            getConvert()->copy(this->src->getPVField(),this->dest->getPVField());

            if(this->destTimestamp.isAttached()){
                this->t.getCurrent();
                this->destTimestamp.set(t);
            }
        });
    }
};

class scanRecord : public iocRecord{
public:
    /**
     * @brief getForm defines records mandatory fields
     * @return
     */
    static StructureConstPtr getForm(){
        cout << "GET FORM!" << endl;
        return getFieldCreate()->createFieldBuilder()->
                add("value",pvInt)->
                add("timestamp",getStandardField()->timeStamp())->
                add("rate",pvDouble)->
                createStructure();
    }

    /**
     * @brief createRecord creates and instance of default record
     * @param name
     * @return
     */
    static iocRecordPtr createRecord(string name,PVStructurePtr data){
        return iocRecordPtr(new scanRecord(name,data));

    }

    scanRecord(string name, PVStructurePtr data):iocRecord(name,data){
    }

    bool init(){
        iocRecord::init();

        //Copy pointers to fields so we don't have to look them up every time
        VALUE = data->getIntField("value");
        TIMESTAMP = data->getStructureField("timestamp");
        RATE = data->getDoubleField("rate");

        //Check if values make sense/set default vals
        if(!RATE->get()) RATE->put(1);

        addFieldHandler(findPVRecordField(VALUE),bind(&scanRecord::onValueChange,this,placeholders::_1));

        string threadName = getRecordName()+"_scanThread";
        epicsThreadCreate(threadName.c_str(),50,epicsThreadStackMedium,&scanRecord::scanThread,this);
    }


    PVIntPtr VALUE;
    PVStructurePtr TIMESTAMP;
    PVDoublePtr RATE;


private:

    static void scanThread(void* arg){
        scanRecord* r = static_cast<scanRecord*>(arg);
        TimeStamp t;
        PVTimeStamp pvT;
        pvT.attach(r->TIMESTAMP);


        while(1){
            r->lock();
            r->VALUE->put(r->VALUE->get()+1);

            t.getCurrent();
            pvT.set(t);

            r->unlock();

            epicsThreadSleep(r->RATE->get());
        }
    }

    void onValueChange(PVRecordFieldPtr const field){
        lock();
        cout << "SCAN RECORD" << endl;
        unlock();
    }
};

void testStandardRecord(){

//    //----------Test standard records-----------//
//    //Create record form
//    StructureConstPtr form = getFieldCreate()->createFieldBuilder()->add("value",pvString)->addArray("data",pvByte)->createStructure();
//    //Create standard record from form
////    iocRecordPtr record = ioc4::getIoc()->createRecordF("STDIN",form);


//    //Add data handler
//    record->addFieldHandler(record->findPVRecordFieldByName("data"),[](PVRecordFieldPtr const field){

//        iocRecordPtr record = static_pointer_cast<iocRecord>(field->getPVRecord());

//        PVStringPtr value = record->data->getStringField("value");
//        PVScalarArrayPtr data = record->data->getScalarArrayField("data",pvByte);

//        string strVal;
//        getConvert()->getString(&strVal,data);

//        value->put(strVal);
//    });

}

void testStandardRecord2(){


}

int main(int argc, char** argv){


//    PVStructurePtr req = CreateRequest::create()->createRequest("process=true,field(test,data)");

    ioc4* ioc = ioc4::getIoc();

    //Register components
    ioc->addFactory("SCAN",&scanRecord::createRecord,&scanRecord::getForm);

    //Create a record using factory
    ioc->createRecord("SCAN","S1");

    //Set records fields
    ioc->setStagingField("S1.timestamp","100 0 23");
    ioc->setStagingField("S1.rate","3");
    ioc->setStagingField("S1.desc","HelloWorld");

    //Intiate record with SCAN implementation
    iocRecordPtr S1 = ioc->initRecord("SCAN","S1");

    //Create record using form defintion
    StructureConstPtr record_form = getFieldCreate()->createFieldBuilder()
            ->add("value",pvDouble)
            ->add("timestamp",getStandardField()->timeStamp())
            ->createStructure();

    ioc->createRecord("TEST2",record_form);
    //Initiate record without implementation (placeholder)
    iocRecordPtr TEST2 = ioc->initRecord("","TEST2");

    ioc->createRecord("TEST3",record_form);
    iocRecordPtr TEST3 = ioc->initRecord("","TEST3");

    //Manually create a a few put links
    ioc4PutLink link(S1->findPVRecordFieldByName("value"),TEST2->findPVRecordFieldByName("value"));
//    ioc4PutLink link1(S1->findPVRecordFieldByName("value"),TEST3->findPVRecordFieldByName("value"));

    ioc4PutLink link2(ioc->findField("S1.timestamp"),ioc->findField("TEST3.timestamp"));



    ioc->findField("S1.value")->getPVField()->dumpValue(cout);





    ioc->startPVAccess();

    while(1){
        epicsThreadSleep(1);
    }



//    PVRecord record = ioc

    return 0;
}
