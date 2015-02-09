
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

    static void bindRecord(iocRecordPtr record){
        new PerfRecord(record);
    }

private:
    PVDoublePtr m_in;
    PVDoublePtr m_out;
    PVDoublePtr m_perf; //in us

    PerfRecord(iocRecordPtr record){
        m_in = dynamic_pointer_cast<PVDouble>(record->findPVRecordFieldByName("in")->getPVField());
        m_out = dynamic_pointer_cast<PVDouble>(record->findPVRecordFieldByName("out")->getPVField());
        m_perf = dynamic_pointer_cast<PVDouble>(record->findPVRecordFieldByName("perf")->getPVField());

        record->addFieldHandler(record->findPVRecordFieldByName("in"),bind(&PerfRecord::process,this));
    }

    void process(){
        struct timespec t_proc_start,t_proc_end;

        //execute link and measure time
        clock_gettime(CLOCK_MONOTONIC,&t_proc_start);
        m_out->put(0.0); //no value
        clock_gettime(CLOCK_MONOTONIC,&t_proc_end);
        //write out the results
        double proc_t = (t_proc_end.tv_sec*1e6 + t_proc_end.tv_nsec/1e3) - (t_proc_start.tv_sec*1e6+t_proc_start.tv_nsec/1e3);
//        printf("%fus\n",proc_t);
        m_perf->put(proc_t);
    }

};


int main(int argc, char** argv){

    StandardRecords::registerStandardRecords();
    ioc4::getIoc()->addComponentFacotry("PERF",PerfRecord::bindRecord);


    ioc4s::init();
    ioc4s::createRecord("TEST:SCAN","STD::SCAN");
    ioc4s::setStagingField("TEST:SCAN.rate","0.1");
    ioc4s::bindRecord("TEST:SCAN","STD::SCAN");

    ioc4s::createRecord("TEST:PERF","UINT");
    ioc4s::addStagingField("TEST:PERF.in","double");
    ioc4s::addStagingField("TEST:PERF.out","double");
    ioc4s::addStagingField("TEST:PERF.perf","double");
    ioc4s::bindRecord("TEST:PERF","PERF");

    ioc4s::createRecord("TEST:DOUBLE","DOUBLE");
    ioc4s::initRecord("TEST:DOUBLE");

    ioc4s::addLink("TEST:SCAN.value","TEST:PERF.in","PUT","");
    ioc4s::addLink("TEST:PERF.out","TEST:DOUBLE.value","PUT","");




    ioc4s::startPVA();
    epicsThreadSleep(1);
    while(1){
        epicsThreadSleep(1);
    }



    //    PVRecord record = ioc

    return 0;
}
