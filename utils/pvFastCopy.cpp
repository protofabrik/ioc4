#include <pv/pvData.h>
#include "pvFastCopy.h"


bool PVFastCopy::addFieldCopy(PVFieldPtr srcField, PVFieldPtr dstField){
    //Scalar, check if types match
    if(srcField->getField()->getType() == scalar){
        //destination field not a scalar
        if(dstField->getField()->getType() != scalar) {return false;}

        PVScalarPtr srcScalar = static_pointer_cast<PVScalar>(srcField);
        PVScalarPtr dstScalar = static_pointer_cast<PVScalar>(dstField);

        //Fields exist but have different scalar types
        if(srcScalar->getScalar()->getScalarType() != dstScalar->getScalar()->getScalarType()) {return false;}

        //Fields exist and match, obtain raw pointers and push them to pipe
        fields_.push_back({srcScalar.get(),dstScalar.get(),srcScalar->getScalar()->getScalarType()});
        return true;
    }

    //Handle nested structures
    if(srcField->getField()->getType() == structure){
        if(dstField->getField()->getType() != structure) {return false;}

        PVStructurePtr srcStruct=static_pointer_cast<PVStructure>(srcField);
        PVStructurePtr dstStruct=static_pointer_cast<PVStructure>(dstField);

        return addCopy(srcStruct,dstStruct);

        //            PVFastCopy c;
        //            //Init and check if the substructures match
        //            if(!c.addCopy(srcStruct,dstStruct)) return false;
        //            structs_.push_back(c);
        //            return true;
    }
    //Handle arrays

    return false;

}

void PVFastCopy::fastScalarCopy(PVScalar *src, PVScalar *dest, ScalarType type){
    switch(type){
    case pvString:
        static_cast<PVString*>(dest)->put(static_cast<PVString*>(src)->get());
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

}

bool PVFastCopy::addCopy(PVFieldPtr src, PVFieldPtr dst){

    //Its a scalar, just add it to the list
    if(src->getField()->getType()==scalar){
        return addFieldCopy(src,dst);
    }

    //Its a structure, iterate over it
    if(src->getField()->getType()==structure){
        PVStructurePtr srcStruct = static_pointer_cast<PVStructure>(src);
        PVStructurePtr dstStruct = static_pointer_cast<PVStructure>(dst);

        fields_.reserve(srcStruct->getPVFields().size());
        //Confirm that the structures can be copied
        for(PVFieldPtr srcField : srcStruct->getPVFields()){
            PVFieldPtr dstField = dstStruct->getSubField(srcField->getFieldName());

            //Destination field doesnt exist
            if(!dstField) return false;
            if(!addFieldCopy(srcField,dstField)) return false;
        }
    }
    return true;
}

void PVFastCopy::doCopy(){
    for(auto &f : fields_){
        fastScalarCopy(f.src,f.dst,f.type);
    }

    //        cout << fields_.size() << endl;
    //        for(int i=0;i<structs_.size();i++){
    //            structs_[i].doCopy();
    //        }

}
