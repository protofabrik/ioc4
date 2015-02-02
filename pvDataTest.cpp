#include <stdlib.h>
#include <stdio.h>



#include <pv/pvData.h>
#include <pv/convert.h>
#include <pv/standardField.h>
#include <pv/standardPVField.h>




using namespace epics::pvData;
using namespace std::tr1;

int main(int argc, char** argv){

    StructureConstPtr recordForm = getFieldCreate()->createFieldBuilder()->
            add("inp1",pvDouble)->
            addArray("out1",pvByte)->
            add("timestamp",getStandardField()->timeStamp())->
            createStructure();

//    recordForm->dump(std::cout);

    PVStructurePtr record = getPVDataCreate()->createPVStructure(recordForm);

//    record->dumpValue(std::cout);

    PVFieldPtr fieldINP = record->getDoubleField("inp1");
    PVFieldPtr fieldINP_clone =  getPVDataCreate()->createPVScalar(pvDouble);

    static_pointer_cast<PVDouble>(fieldINP)->put(10);

    getConvert()->copy(fieldINP,fieldINP_clone);

    fieldINP_clone->dumpValue(std::cout);


    std::cout << "\n################ TEST 2 ############\n";


    PVScalarArrayPtr out1 = record->getSubField<PVScalarArray>("out1");
    PVScalarArrayPtr out1_clone = getPVDataCreate()->createPVScalarArray(pvByte);

    //Generate 1000bytes of data
    PVByteArray::svector data;

    PVByteArray::const_svector cdata;
    PVByteArray::svector data1;


    std::cout << "Generating data\n";
    for(int i=0;i<atoi(argv[1]);i++) data.push_back(i);
    std::cout << "Done";

    out1->putFrom(freeze(data));


    //Clone
    if(atoi(argv[2])){
    std::cout << "cloneing!\n";

    getConvert()->copy(out1,out1_clone);


//    //Get data into cdata
    out1_clone->getAs(cdata);


    if(atoi(argv[3])){
        std::cout << "Modifying clone!\n";
        data1 = thaw(cdata);
        data1[0]=255;
        out1_clone->putFrom(freeze(data1));
    }
    }

//    out1->dumpValue(std::cout);
//    out1_clone->dumpValue(std::cout);




    return 0;
}
