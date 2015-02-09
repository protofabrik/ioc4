#include <iostream>
#include <functional>
#include <vector>
#include <deque>
#include <epicsThread.h>
#include <epicsMessageQueue.h>
#include <string.h>

using namespace std;

struct work_t{
    function<void(string arg)> func;
    string arg;
    int priority = 0; //default priority

    work_t(string arg):arg(arg){}
};

class WorkQueue{
    epicsMessageQueue* m_queue;


public:
    WorkQueue(int size){
        m_queue = new epicsMessageQueue(size,sizeof(work_t));
    }

    void addToQueue(function<void(string)> func, string arg){

        work_t w(arg);
//        w.func=func;
        cout << w.arg << endl;
        char buffer[100];
        memcpy(buffer,&arg,sizeof(arg));
        m_queue->trySend(buffer,sizeof(arg));
    }

    bool doWork(){
        char buffer[100];
        cout << "Worker started" << endl;
        while(int size = m_queue->tryReceive(buffer,sizeof(work_t))!=-1){
            work_t* w = (work_t*) buffer;
            //w.func(w.arg);
            cout<<"RECEIVED:"<<size<<":"<<buffer<<endl;
        }
        return false;
    }

};

class Foob{
public:
    string mesg;

    Foob(string msg):mesg(msg){};

    void hello(string who){
        cout << "Hello " << who << ": " << mesg <<endl;
    }
};

static void worker(void* arg){
    WorkQueue* w = (WorkQueue*) arg;
    w->doWork();
}

int main(int argc, char* argv[]){
    Foob test1("test1");
    Foob test2("test2");


    WorkQueue* q = new WorkQueue(10);
//    epicsThreadCreate("test",epicsThreadPriorityScanHigh,epicsThreadStackMedium,worker,q);

//    epicsThreadCreate("test",epicsThreadPriorityScanHigh,epicsThreadStackMedium,worker,q);

//    epicsThreadCreate("test",epicsThreadPriorityScanHigh,epicsThreadStackMedium,worker,q);

    q->addToQueue(bind(&Foob::hello,test1,placeholders::_1),"I1");
    q->addToQueue(bind(&Foob::hello,test2,placeholders::_1),"I2");
    q->addToQueue(bind(&Foob::hello,test2,placeholders::_1),"I3");

    q->addToQueue(bind(&Foob::hello,test2,placeholders::_1),"I4");
    q->addToQueue(bind(&Foob::hello,test1,placeholders::_1),"I5");
    q->addToQueue(bind(&Foob::hello,test1,placeholders::_1),"I6");

    q->addToQueue(bind(&Foob::hello,test1,placeholders::_1),"I1");
    q->addToQueue(bind(&Foob::hello,test2,placeholders::_1),"I2");
    q->addToQueue(bind(&Foob::hello,test2,placeholders::_1),"I3");

    q->addToQueue(bind(&Foob::hello,test2,placeholders::_1),"I4");
    q->addToQueue(bind(&Foob::hello,test1,placeholders::_1),"I5");
    q->addToQueue(bind(&Foob::hello,test1,placeholders::_1),"I6");

//    epicsThreadSleep(1);
    while(q->doWork());

    delete q;


}

