#include <ioc4.h>
#include <utils/pvFastCopy.h>
#include "../std/standardRecords.h"
#include <time.h>
#include "../luashell/iocLua.h"

int main(int argc, char *argv[])
{
    StructureConstPtr form = getFieldCreate()->
            createFieldBuilder()->
            add("vala",pvDouble)->
            add("valb",pvInt)->
            add("valc",pvString)->
            add("vald",pvDouble)->
            add("timestamp",getStandardField()->timeStamp())->createStructure();

    lua_State* L = luaL_newstate();
    luaL_openlibs(L);


    PVStructurePtr a = getPVDataCreate()->createPVStructure(form);
    a->getDoubleField("vala")->put(3.14);
    a->getStringField("valc")->put("Hello world\n");



    PVDataLua::PVStructureToLua(L,a);
    lua_setglobal(L,"record");


    luaL_dostring(L,"print(record.vala)");
    luaL_dostring(L,"print(record.valc)");
    luaL_dostring(L,"print(record.timestamp)");
    luaL_dostring(L,"print(record.timestamp.nanoseconds)");

    luaL_dostring(L,"record.vala=record.vala*2");
    luaL_dostring(L,"record.valb=record.vala*2");
    luaL_dostring(L,"record.valc='Hi From Lua'");

    lua_getglobal(L,"record");
    PVDataLua::luaToPVStructure(L,a);

    a->dumpValue(cout);

    PVDataLua::luaToNewPVStructure(L)->dumpValue(cout);
    lua_pop(L,1);


    while(1){

        PVStructurePtr dstStruc = getPVDataCreate()->createPVStructure(form);
        struct timespec t_proc_start,t_proc_end;
        double proc_t;


        clock_gettime(CLOCK_MONOTONIC,&t_proc_start);
        for(int i=0;i<1000;i++){
            PVDataLua::PVStructureToLua(L,a);
            lua_setglobal(L,"record");
        }
        clock_gettime(CLOCK_MONOTONIC,&t_proc_end);
        proc_t = (t_proc_end.tv_sec*1e6 + t_proc_end.tv_nsec/1e3) - (t_proc_start.tv_sec*1e6+t_proc_start.tv_nsec/1e3);
        printf("Took %f us to serialize to Lua\n",proc_t/1000);



        clock_gettime(CLOCK_MONOTONIC,&t_proc_start);
        for(int i=0;i<1000;i++){
            lua_getglobal(L,"record");
            PVDataLua::luaToPVStructure(L,dstStruc);
            lua_pop(L,1);
        }
        clock_gettime(CLOCK_MONOTONIC,&t_proc_end);
        proc_t = (t_proc_end.tv_sec*1e6 + t_proc_end.tv_nsec/1e3) - (t_proc_start.tv_sec*1e6+t_proc_start.tv_nsec/1e3);
        printf("Took %f us to deserialize from Lua to existing structure\n",proc_t/1000);



        clock_gettime(CLOCK_MONOTONIC,&t_proc_start);
        for(int i=0;i<1000;i++){
            lua_getglobal(L,"record");
            PVDataLua::luaToNewPVStructure(L);
            lua_pop(L,1);
        }
        clock_gettime(CLOCK_MONOTONIC,&t_proc_end);
        proc_t = (t_proc_end.tv_sec*1e6 + t_proc_end.tv_nsec/1e3) - (t_proc_start.tv_sec*1e6+t_proc_start.tv_nsec/1e3);
        printf("Took %f us to deserialize from Lua to new structure\n",proc_t/1000);

        sleep(1);
    }

}
