
#include <pv/pvTimeStamp.h>
#include "ioc4.h"
#include "iocUtils.h"
#include <pv/channelProviderLocal.h>

#include <lua.hpp>

#include "std/standardRecords.h"

#include <time.h>
#include <functional>


class PerfRecord{
public:

    static StructureConstPtr getForm(){
        return getFieldCreate()->createFieldBuilder()->
                add("in",pvUInt)->
                add("out",pvUInt)->
                add("nruns",pvUInt)->
                add("perf",pvDouble)->
                createStructure();
    }

    static void bindRecord(iocRecordPtr record){
        new PerfRecord(record);
    }

private:
    PVUIntPtr m_in;
    PVUIntPtr m_out;
    PVUIntPtr m_nruns;
    PVDoublePtr m_perf; //in us

    PerfRecord(iocRecordPtr record){
        m_in = dynamic_pointer_cast<PVUInt>(record->findPVRecordFieldByName("in")->getPVField());
        m_out = dynamic_pointer_cast<PVUInt>(record->findPVRecordFieldByName("out")->getPVField());
        m_nruns = dynamic_pointer_cast<PVUInt>(record->findPVRecordFieldByName("nruns")->getPVField());
        m_perf = dynamic_pointer_cast<PVDouble>(record->findPVRecordFieldByName("perf")->getPVField());



        record->addFieldHandler(record->findPVRecordFieldByName("in"),bind(&PerfRecord::process,this));
    }

    void process(){
        struct timespec t_proc_start,t_proc_end;

        //execute link for n iterations and measure time
        clock_gettime(CLOCK_MONOTONIC,&t_proc_start);
        for(int i=0;i<m_nruns->get();i++)
            m_out->put(m_in->get()); //copy in to out

        clock_gettime(CLOCK_MONOTONIC,&t_proc_end);

        //write out the results
        double proc_t = (t_proc_end.tv_sec*1e6 + t_proc_end.tv_nsec/1e3) - (t_proc_start.tv_sec*1e6+t_proc_start.tv_nsec/1e3);
        proc_t=proc_t/m_nruns->get();

//        printf("%fus\n",proc_t);
        m_perf->put(proc_t);
    }

};


int main(int argc, char** argv){

    StandardRecords::registerStandardRecords();
    ioc4::getIoc()->addComponentFacotry("PERF",PerfRecord::bindRecord);
    ioc4::getIoc()->addRecordFactory("PERF",PerfRecord::getForm);


    ioc4s::init();
    ioc4s::createRecord("TEST:SCAN","STD::SCAN");
    ioc4s::setStagingField("TEST:SCAN.rate","0.1");
    ioc4s::bindRecord("TEST:SCAN","STD::SCAN");

    ioc4s::createRecord("TEST:PERF","PERF");
    ioc4s::setStagingField("TEST:PERF.nruns","1");
    ioc4s::bindRecord("TEST:PERF","PERF");

    ioc4s::createRecord("TEST:DOUBLE","UINT");
    ioc4s::initRecord("TEST:DOUBLE");

    ioc4s::addLink("TEST:SCAN.value","TEST:PERF.in","PUT","");
    ioc4s::addLink("TEST:PERF.out","TEST:DOUBLE.value","PUT","");




    for(int i=0;i<1000;i++){
        string recordName="TEST:P" + std::to_string(i);
        cout << "Adding new record " << recordName << endl;

        ioc4s::createRecord(recordName,"PERF");
        ioc4s::setStagingField(recordName+".nruns","1");
        ioc4s::bindRecord(recordName,"PERF");

        if(i)
            ioc4s::addLink("TEST:P"+std::to_string(i-1)+".out","TEST:P"+std::to_string(i)+".in","PUT","");
    }

    ioc4s::addLink("TEST:SCAN.value","TEST:P0.in","PUT","");



    ioc4s::startPVA();
    epicsThreadSleep(1);
    while(1){
        epicsThreadSleep(1);
    }



    //    PVRecord record = ioc

    return 0;
}
