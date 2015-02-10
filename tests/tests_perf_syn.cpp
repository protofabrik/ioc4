#include <ioc4.h>
#include <utils/pvFastCopy.h>
#include "../std/standardRecords.h"
#include <time.h>


int main(int argc, char *argv[])
{
    ioc4* ioc4 = ioc4::getIoc();
    StandardRecords::registerStandardRecords();

    ioc4->createRecord("TEST","DOUBLE");

    iocRecordPtr record = ioc4->initRecord("TEST");

    PVStructurePtr source = getPVDataCreate()->createPVStructure(record->data);
    PVDoublePtr val = source->getDoubleField("value");

    if(!val) throw runtime_error("NO VAL");

    PVFastCopy c;
    if(!c.addCopy(source->getSubField("value"),record->findPVField("value"))) throw runtime_error("CANNOT COPY");


    ioc4->startPVAccess();

    while(1){

        struct timespec t_proc_start,t_proc_end;
        double proc_t;
        clock_gettime(CLOCK_MONOTONIC,&t_proc_start);
        for(int i=0;i<4;i++){
            val->put(i);
            c.doCopy();
        }
        clock_gettime(CLOCK_MONOTONIC,&t_proc_end);
        proc_t = (t_proc_end.tv_sec*1e6 + t_proc_end.tv_nsec/1e3) - (t_proc_start.tv_sec*1e6+t_proc_start.tv_nsec/1e3);
        printf("Took %f us per run\n",proc_t/4);

        sleep(1);

//    record->data->dumpValue(cout);

    }


}
