#ifndef LUARECORD_H_DEF
#define LUARECORD_H_DEF

#include "../ioc4.h"

#include <functional>


#include "lua.hpp"
#include <luabind/luabind.hpp>
#include <luabind/function.hpp>
#include "luaRecord.h"


using namespace  std;

class LuaRecord{
public:
//    static StructureConstPtr getForm();


    static void init(iocRecordPtr record){
        //Update lua record path
        if(std::getenv("IOC4_LUA_RECORDS")){
             m_lua_record_path = std::getenv("IOC4_LUA_RECORDS");
        }
        else{
            char cwd[255];
            getcwd(cwd,255);
            m_lua_record_path = string(cwd)+"/luarecords";
        }

        new LuaRecord(record);
    }

private:
    static string m_lua_record_path;

    iocRecordPtr m_record;
    PVStringPtr m_code;
    bool m_running;
    lua_State* L;

    PVRecordFieldPtrArrayPtr m_fields;


    LuaRecord(iocRecordPtr record);

    /**
     * @brief code_updated
     *
     * this function is called when .code field is updated. The code field is supposed to contain valid lua code.
     * If code is not valid parsing error will be printed to STDOUT
     */
    void code_updated();

    /**
     * @brief run
     * This function is called whenever any of the fields is updated. The function executes function that corresponds to <field name>_ (.e.g value_())
     * @param updatedField
     */
    void run(PVRecordFieldPtr const updatedField);

    void copyFieldsToLua();
    void copyFieldsFromLua();
};

#endif
