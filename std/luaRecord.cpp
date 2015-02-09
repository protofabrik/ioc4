#include "../ioc4.h"

#include <functional>


#include "lua.hpp"
#include "luaRecord.h"



using namespace  std;


string LuaRecord::m_lua_record_path;

LuaRecord::LuaRecord(iocRecordPtr record):m_record(record){
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

    copyFieldsToLua();

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

    copyFieldsFromLua();

    m_record->unlock();
}

#include "../luashell/iocLua.h"
void LuaRecord::run(const PVRecordFieldPtr updatedField){
    m_record->lock();

    copyFieldsToLua();

    //New way of copying data to Lua
//    PVDataLua::PVStructureToLua(L,m_record->getPVRecordStructure()->getPVStructure());
//    lua_setglobal(L,"record");

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

    copyFieldsFromLua();

//    lua_gc(L,LUA_GCCOLLECT,0);
    m_record->unlock();
}

void LuaRecord::copyFieldsToLua(){
    //Copy fields into global Lua scope
    PVRecordFieldPtr field;
    for(int i=0;i<m_fields->size();i++){
        field = m_fields->at(i);

        PVFieldPtr d = field->getPVField();


        //Check if it is string and copy it
        PVStringPtr strVal = dynamic_pointer_cast<PVString>(d);
        if(strVal){
            //luabind::globals(L)[d->getFieldName()] = strVal->get();
            lua_pushstring(L,strVal->get().c_str());
            lua_setglobal(L,d->getFieldName().c_str());
        }

        //Check if it is double and copy it
        PVDoublePtr dbVal = dynamic_pointer_cast<PVDouble>(d);
        if(dbVal){
            lua_pushnumber(L,dbVal->get());
            lua_setglobal(L,d->getFieldName().c_str());
        }


    }
}
void LuaRecord::copyFieldsFromLua(){
    //extract the values from lua scope
    PVRecordFieldPtr field;
    for(int i=0;i<m_fields->size();i++){
        field = m_fields->at(i);

        PVFieldPtr d = field->getPVField();

        //Push lua representation of this field to stack
        lua_getglobal(L,d->getFieldName().c_str());

        //Check if it is string and copy it
        PVStringPtr strVal = dynamic_pointer_cast<PVString>(d);
        if(strVal && lua_isstring(L,-1)){
            string val(lua_tostring(L,-1));

            //Only update the field if it changed
            if(val != strVal->get())
                strVal->put(val);
        }

        //Check if it is double and copy it
        PVDoublePtr dbVal = dynamic_pointer_cast<PVDouble>(d);
        if(dbVal && lua_isnumber(L,-1)){
            double val = lua_tonumber(L,-1);
            if(val != dbVal->get())
                dbVal->put(val);
        }

        //Pop the value from stack
        lua_pop(L,1);

    }
}
