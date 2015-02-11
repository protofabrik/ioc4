#include "../ioc4.h"

#include <functional>


#include "lua.hpp"
#include "luaRecord.h"
#include "../luashell/iocLua.h"




using namespace  std;


string LuaRecord::m_lua_record_path;

LuaRecord::LuaRecord(iocRecordPtr record):
    m_record(record),
    m_running(false)

    {
    //Oh noes, unguarded record lock. If exception is thrown here we will neve unlock this record.
    //TODO: Scoped locks...
    m_record->lock();

    try{
        m_code = dynamic_pointer_cast<PVString>(record->findPVRecordFieldByName("code")->getPVField());
        //m_code field exists, add a handler to it
        record->addFieldHandler(record->findPVRecordField(m_code) ,bind(&LuaRecord::code_updated,this));

    }catch(runtime_error &e){
        //If the record doesn't have a field code, we create a new instance of PVString for internal use
        m_code=static_pointer_cast<PVString>(getPVDataCreate()->createPVScalar(pvString));
        //throw runtime_error("Lua record "+record->getRecordName()+" does not have field code");
    }


    m_fields = record->getPVRecordStructure()->getPVRecordFields();
    //Intiate Lua
    L=luaL_newstate();
    luaL_openlibs(L);


    //Check if luarecord field exists
    {
        PVStringPtr luarecordField;
        try{
            luarecordField = dynamic_pointer_cast<PVString>(record->findPVField("luarecord"));
        }catch(runtime_error e){
            luarecordField = PVStringPtr();
        }

        if(luarecordField){
            //Copy code to code field
            string path = m_lua_record_path+"/"+luarecordField->get();
            cout << "Loading lua record: " << path << endl;
            std::ifstream t(path);
            if(!t.is_open()){
                throw runtime_error("Could not open lua record: "+path);
            }

            std::stringstream buffer;
            buffer << t.rdbuf();
            m_code->put(buffer.str());
        }
    }

    //Apply default values
    code_updated();
    //Add handler to code updated

    //Add hanlder to all other fields
    PVRecordFieldPtr field;
    for(int i=0;i<m_fields->size();i++){
        field = m_fields->at(i);
        record->addFieldHandler(field,bind(&LuaRecord::run,this,placeholders::_1));
    }

    m_record->unlock();
}

void LuaRecord::code_updated(){
    m_record->lock();

    //Evaluate new code
    if(luaL_dostring(L,m_code->get().c_str())){
        cout << "Error in Lua record " << m_record->getRecordName() << endl;
        cout << "could not parse Lua code..." << endl;
        cout << lua_tostring(L,-1)<<endl;
        cout << "Code dump : "<< endl;
        cout << m_code->get() << endl;

    }

    //copyFieldsToLua();
    PVDataLua::PVStructureToLua(L,m_record->data);
    lua_setglobal(L,"record");


    //Run init function if it exists
    lua_getglobal(L,"init");
    if(lua_isfunction(L,-1)){
        if (lua_pcall(L, 0, 0, 0) != 0){
            cout << "Error in Lua record " << m_record->getRecordName() << endl;
            cout << "could not execute Lua code..." << endl;
            cout << lua_tostring(L,-1)<<endl;
        }
    }else{
        lua_pop(L,1);
    }

    //copyFieldsFromLua();
    lua_getglobal(L,"record");
    PVDataLua::luaToPVStructure(L,m_record->data);
    lua_pop(L,1);

    m_record->unlock();
}

void LuaRecord::run(const PVRecordFieldPtr updatedField){
    //Prevent multiple calls to run due to changeing fields
    if(m_running) return;

    m_record->lock();
    cout << "LUA PROC!!" << updatedField->getFullFieldName() << endl;
    m_running=true;

    //    copyFieldsToLua();
    PVDataLua::PVStructureToLua(L,m_record->data);
    lua_setglobal(L,"record");

    //Run function if it exists
    lua_getglobal(L,(updatedField->getFullFieldName()+"_").c_str());
    if(lua_isfunction(L,-1)){
        if (lua_pcall(L, 0, 0, 0) != 0){
            cout << "Error in Lua record " << m_record->getRecordName() << endl;
            cout << "could not execute Lua code..." << endl;
            cout << lua_tostring(L,-1)<<endl;
        }
    }else{
        lua_pop(L,1);
    }

    //copyFieldsFromLua();
    lua_getglobal(L,"record");
    PVDataLua::luaToPVStructure(L,m_record->data);
    lua_pop(L,1);
    m_running=false;
    cout << "LUA PROC END!!" << endl;

//    lua_gc(L,LUA_GCCOLLECT,0);
    m_record->unlock();
}
