
#include <pv/pvData.h>
#include <pv/convert.h>
#include <time.h>
#include <functional>
#include <pv/pvCopy.h>
#include <utils/pvFastCopy.h>




using namespace epics::pvData;
using namespace std;

#include <pv/standardField.h>

void copyTest(){

    StructureConstPtr form = getFieldCreate()->
            createFieldBuilder()->
            add("vala",pvDouble)->
            add("valb",pvInt)->
            add("valc",pvString)->
            add("vald",pvDouble)->
            add("timestamp",getStandardField()->timeStamp())->createStructure();


    PVStructurePtr a = getPVDataCreate()->createPVStructure(form);
    PVStructurePtr b = getPVDataCreate()->createPVStructure(form);

    PVDoublePtr a_perf = a->getDoubleField("vala");
    PVDoublePtr b_perf = b->getDoubleField("vala");

    struct timespec t_proc_start,t_proc_end;

    ConvertPtr convert = getConvert();
    double proc_t;

    cout << "Measuring copyScalar perfromance" << endl;
    clock_gettime(CLOCK_MONOTONIC,&t_proc_start);
    for(int i=0;i<100000;i++){
        convert->copyScalar(a_perf,b_perf);
    }
    clock_gettime(CLOCK_MONOTONIC,&t_proc_end);
    proc_t = (t_proc_end.tv_sec*1e6 + t_proc_end.tv_nsec/1e3) - (t_proc_start.tv_sec*1e6+t_proc_start.tv_nsec/1e3);
    printf("Took %f us per copy\n",proc_t/100000);


    cout << "Measuring put perfromance" << endl;
    clock_gettime(CLOCK_MONOTONIC,&t_proc_start);
    for(int i=0;i<100000;i++){
        a_perf->put(random());
        b_perf->put(a_perf->get());
    }
    clock_gettime(CLOCK_MONOTONIC,&t_proc_end);
    proc_t = (t_proc_end.tv_sec*1e6 + t_proc_end.tv_nsec/1e3) - (t_proc_start.tv_sec*1e6+t_proc_start.tv_nsec/1e3);
    printf("Took %f us per copy\n",proc_t/100000);

    cout << "Measuring copy perfromance" << endl;
    clock_gettime(CLOCK_MONOTONIC,&t_proc_start);
    for(int i=0;i<100000;i++){
        a_perf->put(random());
        convert->copy(a,b);
    }
    clock_gettime(CLOCK_MONOTONIC,&t_proc_end);
    proc_t = (t_proc_end.tv_sec*1e6 + t_proc_end.tv_nsec/1e3) - (t_proc_start.tv_sec*1e6+t_proc_start.tv_nsec/1e3);
    printf("Took %f us per copy\n",proc_t/100000);

    cout << "Measuring fastscalar copy perfromance" << endl;
    clock_gettime(CLOCK_MONOTONIC,&t_proc_start);
    for(int i=0;i<1000000;i++){
        a_perf->put(random());
//        PVFastCopy::fastScalarCopy(a_perf.get(),b_perf.get(),pvDouble);
    }
    clock_gettime(CLOCK_MONOTONIC,&t_proc_end);
    proc_t = (t_proc_end.tv_sec*1e6 + t_proc_end.tv_nsec/1e3) - (t_proc_start.tv_sec*1e6+t_proc_start.tv_nsec/1e3);
    printf("Took %f us per copy\n",proc_t/1000000);


    cout << "Measuring fastCopy perfromance" << endl;

    PVFastCopy co;
    if(!co.addCopy(a,b)){
        throw runtime_error("Cannot copy a -> b");
    }

    clock_gettime(CLOCK_MONOTONIC,&t_proc_start);
    for(int i=0;i<100000;i++){
        a_perf->put(random());
        co.doCopy();
    }
    clock_gettime(CLOCK_MONOTONIC,&t_proc_end);
    proc_t = (t_proc_end.tv_sec*1e6 + t_proc_end.tv_nsec/1e3) - (t_proc_start.tv_sec*1e6+t_proc_start.tv_nsec/1e3);
    printf("Took %f us per copy\n",proc_t/100000);

    /////////////////////////////////??????????///////////////////////////
    cout << "Measuring fastCopy scalar perfromance" << endl;

    PVFastCopy co1;
    if(!co1.addCopy(a->getSubField("vala"),b->getSubField("vala"))){
        throw runtime_error("Cannot copy a -> b");
    }

    clock_gettime(CLOCK_MONOTONIC,&t_proc_start);
    for(int i=0;i<100000;i++){
        a_perf->put(random());
        co1.doCopy();
    }
    clock_gettime(CLOCK_MONOTONIC,&t_proc_end);
    proc_t = (t_proc_end.tv_sec*1e6 + t_proc_end.tv_nsec/1e3) - (t_proc_start.tv_sec*1e6+t_proc_start.tv_nsec/1e3);
    printf("Took %f us per copy\n",proc_t/100000);

}

void fastScalarCopyTest(){
    //Copy from one producer to multiple consumers
    StructureConstPtr form = getFieldCreate()->
            createFieldBuilder()->
            add("vala",pvDouble)->
            add("valb",pvInt)->
            add("valc",pvString)->
            add("vald",pvDouble)->
            add("timestamp",getStandardField()->timeStamp())->createStructure();

    PVStructurePtr producer = getPVDataCreate()->createPVStructure(form);

    PVStructureArrayPtr consumers = getPVDataCreate()->createPVStructureArray(form);

    //Create a 1000 consumers
    consumers->append(1000);

    PVFastCopy co;

    PVDoublePtr val = producer->getDoubleField("vala");
    producer->getIntField("valb")->put(42);
    producer->getStructureField("timestamp")->getIntField("nanoseconds")->put(314000);


    for(auto consumer : consumers->view()){
        if(!co.addCopy(producer,consumer)){
            printf("a->b is not copybale\n");
        }
    }

    cout << "Array length: " << consumers->getLength() << endl;


    cout << "Measuring PVFastCopy perfromance in fanout config" << endl;
    struct timespec t_proc_start,t_proc_end;
    double proc_t;
    clock_gettime(CLOCK_MONOTONIC,&t_proc_start);
    for(int i=0;i<10000;i++){
        val->put(3.14);
        co.doCopy();
    }
    clock_gettime(CLOCK_MONOTONIC,&t_proc_end);
    proc_t = (t_proc_end.tv_sec*1e6 + t_proc_end.tv_nsec/1e3) - (t_proc_start.tv_sec*1e6+t_proc_start.tv_nsec/1e3);
    printf("Took %f us per copy\n",proc_t/10000);


    consumers->view().at(32)->dumpValue(cout);
}


int main(int argc, char** argv){

    copyTest();
    fastScalarCopyTest();
    return 0;
}
