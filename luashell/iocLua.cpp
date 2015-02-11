
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

    const PVFieldPtrArray fields = pv_struct->getPVFields();

    lua_newtable(L);

    for(int i=0;i<fields.size();i++){
        PVFieldPtr field=fields[i];
        //Handle scalar conversion
        if(field->getField()->getType()==scalar){
            //PVDoublePtr dval = dynamic_pointer_cast<PVDouble>(field);
            ScalarType type = static_cast<const Scalar*>(field->getField().get())->getScalarType();

            switch (type) {
            case pvDouble:
                lua_pushnumber(L,static_cast<PVDouble*>(field.get())->get());
                lua_setfield(L,-2,field->getFieldName().c_str());
                break;
            case pvByte:
                lua_pushnumber(L,static_cast<PVByte*>(field.get())->get());
                lua_setfield(L,-2,field->getFieldName().c_str());
                break;
            case pvUByte:
                lua_pushnumber(L,static_cast<PVUByte*>(field.get())->get());
                lua_setfield(L,-2,field->getFieldName().c_str());
                break;
            case pvShort:
                lua_pushnumber(L,static_cast<PVShort*>(field.get())->get());
                lua_setfield(L,-2,field->getFieldName().c_str());
                break;
            case pvUShort:
                lua_pushnumber(L,static_cast<PVUShort*>(field.get())->get());
                lua_setfield(L,-2,field->getFieldName().c_str());
                break;
            case pvInt:
                lua_pushnumber(L,static_cast<PVInt*>(field.get())->get());
                lua_setfield(L,-2,field->getFieldName().c_str());
                break;
            case pvUInt:
                lua_pushnumber(L,static_cast<PVUInt*>(field.get())->get());
                lua_setfield(L,-2,field->getFieldName().c_str());
                break;
            case pvLong:
                lua_pushnumber(L,static_cast<PVLong*>(field.get())->get());
                lua_setfield(L,-2,field->getFieldName().c_str());
                break;
            case pvULong:
                lua_pushnumber(L,static_cast<PVULong*>(field.get())->get());
                lua_setfield(L,-2,field->getFieldName().c_str());
                break;
            case pvString:
                lua_pushstring(L,static_cast<PVString*>(field.get())->get().c_str());
                lua_setfield(L,-2,field->getFieldName().c_str());
                break;
            default:
                throw runtime_error("Conversion not yet implemented!");
                break;
            }

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

void PVDataLua::luaToPVStructure(lua_State *L, PVStructure* dstStructure){
    //Iterate over table fields
    /* table is in the stack at index '-1' */
    lua_pushnil(L);  /* first key, table at index -2 */
    while (lua_next(L, -2) != 0) {

        /* uses 'key' (at index -2) and 'value' (at index -1) */
        //        printf("%s - %s\n",lua_tostring(L,-2),lua_tostring(L,-1));

        //Check if field exists in structure
        PVField* f = dstStructure->getSubField(lua_tostring(L,-2)).get();
        if(f){
            //Recursion
            if(lua_istable(L,-1)){
                //Check if field is structure
                if(f->getField()->getType() == structure)
                    PVDataLua::luaToPVStructure(L,static_cast<PVStructure*>(f));
            }

            //Check if field is scalar
            else if(f->getField()->getType() == scalar){
                PVScalar* s = static_cast<PVScalar*>(f);
                ScalarType stype = s->getScalar()->getScalarType();

                if(lua_isboolean(L,-1)){
                    if(stype==pvBoolean){
                        static_cast<PVBoolean*>(s)->put(lua_toboolean(L,-1));
                    }
                }
                else if(lua_isnumber(L,-1)){
                    if(stype==pvByte)
                        static_cast<PVByte*>(s)->put(lua_tonumber(L,-1));
                    if(stype==pvShort)
                        static_cast<PVShort*>(s)->put(lua_tonumber(L,-1));
                    if(stype==pvInt)
                        static_cast<PVInt*>(s)->put(lua_tonumber(L,-1));
                    if(stype==pvLong)
                        static_cast<PVLong*>(s)->put(lua_tonumber(L,-1));
                    if(stype==pvUByte)
                        static_cast<PVUByte*>(s)->put(lua_tonumber(L,-1));
                    if(stype==pvUShort)
                        static_cast<PVUShort*>(s)->put(lua_tonumber(L,-1));
                    if(stype==pvUInt)
                        static_cast<PVUInt*>(s)->put(lua_tonumber(L,-1));
                    if(stype==pvULong)
                        static_cast<PVULong*>(s)->put(lua_tonumber(L,-1));
                    if(stype==pvDouble)
                        static_cast<PVDouble*>(s)->put(lua_tonumber(L,-1));
                }
                else if(lua_isstring(L,-1)){
                    if(stype==pvString)
                        static_cast<PVString*>(s)->put(lua_tostring(L,-1));
                }
            }
        }




        /* removes 'value'; keeps 'key' for next iteration */
        lua_pop(L, 1);
    }

}

PVStructurePtr PVDataLua::luaToNewPVStructure(lua_State *L){
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
            data=appendPVField(data,lua_tostring(L,-2),luaToNewPVStructure(L));
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
