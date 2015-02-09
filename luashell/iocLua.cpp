
#include <cstdlib>
#include <functional>

#include <pv/pvTimeStamp.h>

#include "iocLua.h"
#include "../ioc4.h"
#include "../iocUtils.h"
#include "../std/standardRecords.h"

//External includes
extern "C"{
    #include <lua.h>
    #include <unistd.h>
}

#include <luabind/luabind.hpp>
#include <luabind/iterator_policy.hpp>

void newRecord(iocRecordPtr rec){
}

void testing_ground(){
    StandardRecords::registerStandardRecords();

    //New record handler
    ioc4::getIoc()->sig_recordInDatabase+=[](iocRecordPtr rec){
        //cout << "New record added to database "<<rec->getRecordName()<<endl;
    };
}

extern "C" int init_lib(lua_State* L)
{
    testing_ground();;

    using namespace luabind;
    open(L);

    module(L)
    [
        namespace_("ioc")[
            def("init",&ioc4s::init),
            def("createRecord",&ioc4s::createRecord),
            def("bindRecord",&ioc4s::bindRecord),
            def("initRecord",&ioc4s::initRecord),
            def("setStagingField",&ioc4s::setStagingField),
            def("addStagingField",&ioc4s::addStagingField),
            def("startPVAccess",&ioc4s::startPVA),
            def("addLink",&ioc4s::addLink),
            def("dbl",&ioc4s::dbl,return_stl_iterator)
        ]

    ];

//    init1(L);

    return 0;
}


void PVDataLua::PVStructureToLua(lua_State *L, PVStructurePtr pv_struct){

    PVFieldPtrArray fields = pv_struct->getPVFields();

    lua_newtable(L);


    for(int i=0;i<fields.size();i++){
        PVFieldPtr field=fields[i];
        //Handle scalar conversion
        if(field->getField()->getType()==scalar){
            PVDoublePtr dval = dynamic_pointer_cast<PVDouble>(field);
            if(dval){
                lua_pushnumber(L,dval->get());
                lua_setfield(L,-2,field->getFieldName().c_str());
                continue;
            }

            PVStringPtr sval = dynamic_pointer_cast<PVString>(field);
            if(sval){
                lua_pushstring(L,sval->get().c_str());
                lua_setfield(L,-2,field->getFieldName().c_str());
                continue;
            }

            PVIntPtr ival = dynamic_pointer_cast<PVInt>(field);
            if(ival){
                lua_pushnumber(L,ival->get());
                lua_setfield(L,-2,field->getFieldName().c_str());
                continue;
            }

            lua_pushstring(L,"Conversion not yet implemented!");
            lua_setfield(L,-2,field->getFieldName().c_str());

        }

        if(field->getField()->getType()==structure){
            //Recursivly call itself untill whole structure is serialized
            PVStructureToLua(L,dynamic_pointer_cast<PVStructure>(field));
            lua_setfield(L,-2,field->getFieldName().c_str());
        }

    }
}

PVStructurePtr PVDataLua::appendPVField(PVStructurePtr orig, string name, PVFieldPtr field){
    //Create new form with addtional field
    StructureConstPtr newForm = getFieldCreate()->appendField(orig->getStructure(),name,field->getField());
    //Create new data from the form
    PVStructurePtr newData = getPVDataCreate()->createPVStructure(newForm);
    //Copy existing data to new record
    for(PVFieldPtr a : orig->getPVFields()){
        getConvert()->copy(a,newData->getSubField(a->getFieldName()));
    }
    //Copy new data
    getConvert()->copy(field,newData->getSubField(name));

    return newData;
}

PVStructurePtr PVDataLua::luaToPVStructure(lua_State *L){
    if(!lua_istable(L,-1)){
        return PVStructurePtr();
    }

    //Create empty structure
    PVStructurePtr data = getPVDataCreate()->createPVStructure(getFieldCreate()->createFieldBuilder()->createStructure());

    //Iterate over filds
    /* table is in the stack at index '-1' */
    lua_pushnil(L);  /* first key, table at index -2 */
    while (lua_next(L, -2) != 0) {
        /* uses 'key' (at index -2) and 'value' (at index -1) */
        //        printf("%s - %s\n",lua_tostring(L,-2),lua_tostring(L,-1));

        //Recursion
        if(lua_istable(L,-1)){
            data=appendPVField(data,lua_tostring(L,-2),luaToPVStructure(L));
        }
        else if(lua_isboolean(L,-1)){
            //serialization to PVBoolean
            PVBooleanPtr val = static_pointer_cast<PVBoolean>(getPVDataCreate()->createPVScalar(pvBoolean));
            val->put(lua_toboolean(L,-1));
            //Append field
            data=appendPVField(data,lua_tostring(L,-2),val);
        }
        else if(lua_isnumber(L,-1)){
            //serialization to PVDouble
            PVDoublePtr doubleVal = static_pointer_cast<PVDouble>(getPVDataCreate()->createPVScalar(pvDouble));
            doubleVal->put(lua_tonumber(L,-1));
            //Append field
            data=appendPVField(data,lua_tostring(L,-2),doubleVal);
        }
        else if(lua_isstring(L,-1)){
            //serialization to PVString
            PVStringPtr strVal = static_pointer_cast<PVString>(getPVDataCreate()->createPVScalar(pvString));
            strVal->put(lua_tostring(L,-1));
            //Append field
            data=appendPVField(data,lua_tostring(L,-2),strVal);
        }


        /* removes 'value'; keeps 'key' for next iteration */
        lua_pop(L, 1);
    }

    return data;
}
