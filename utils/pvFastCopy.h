#include <pv/pvData.h>


using namespace epics::pvData;
using namespace std;

class PVFastCopy{

    struct copyField{
        PVScalar* src;
        PVScalar* dst;
        ScalarType type;
    };

    vector<copyField> fields_;
    vector<PVFastCopy> structs_;



    inline bool addFieldCopy(PVFieldPtr srcField, PVFieldPtr dstField);

public:


    inline void static fastScalarCopy(PVScalar* src, PVScalar* dest, ScalarType type);


    //Returns true if structures can be copied, false otherwise
    bool addCopy(PVFieldPtr src, PVFieldPtr dst);

    //Preform the actual copy
    void doCopy();


};

