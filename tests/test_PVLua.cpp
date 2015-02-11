#include <lua.hpp>
#include <pv/pvData.h>


using namespace epics::pvData;
using namespace std;

class PVLua{

    struct copyField{
        PVScalar* field;
        ScalarType type;
    };

    vector<copyField> fields_;


    inline bool addFieldCopy(PVFieldPtr srcField)
    {
        //Scalar, check if types match
        if(srcField->getField()->getType() == scalar){
            PVScalarPtr srcScalar = static_pointer_cast<PVScalar>(srcField);
            fields_.push_back({srcScalar.get(),srcScalar->getScalar()->getScalarType()});
            return true;
        }

        //Handle nested structures
        if(srcField->getField()->getType() == structure){
            PVStructurePtr srcStruct=static_pointer_cast<PVStructure>(srcField);
            return addCopy(srcStruct);

        }
        //Handle arrays
        throw runtime_error("Can not convert PVStructure "+srcField->getFieldName()+" to Lua");

        return false;
    }

public:


    inline void static scalarToLua(PVScalar* src, ScalarType type,lua_State* L){
        switch(type){
        case pvString:
            lua_tostring(L,static_cast<PVString*>(src)->get());
            break;
        case pvDouble:
            static_cast<PVDouble*>(dest)->put(static_cast<PVDouble*>(src)->get());
            break;
        case pvInt:
            static_cast<PVInt*>(dest)->put(static_cast<PVInt*>(src)->get());
            break;
        case pvBoolean:
            static_cast<PVBoolean*>(dest)->put(static_cast<PVBoolean*>(src)->get());
            break;
        case pvByte:
            static_cast<PVByte*>(dest)->put(static_cast<PVByte*>(src)->get());
            break;
        case pvFloat:
            static_cast<PVFloat*>(dest)->put(static_cast<PVFloat*>(src)->get());
            break;
        case pvLong:
            static_cast<PVLong*>(dest)->put(static_cast<PVLong*>(src)->get());
            break;
        case pvShort:
            static_cast<PVShort*>(dest)->put(static_cast<PVShort*>(src)->get());
            break;
        case pvUByte:
            static_cast<PVUByte*>(dest)->put(static_cast<PVUByte*>(src)->get());
            break;
        case pvUInt:
            static_cast<PVUInt*>(dest)->put(static_cast<PVUInt*>(src)->get());
            break;
        case pvULong:
            static_cast<PVULong*>(dest)->put(static_cast<PVULong*>(src)->get());
            break;
        case pvUShort:
            static_cast<PVUShort*>(dest)->put(static_cast<PVUShort*>(src)->get());
            break;


        default:
            throw runtime_error("Copy not yet fully implemented!");


    }


    //Returns true if structures can be copied, false otherwise
    bool addCopy(PVFieldPtr src);

    //Preform the actual copy
    void doCopy();


};

int main(int argc, char *argv[])
{

    return 0;
}
