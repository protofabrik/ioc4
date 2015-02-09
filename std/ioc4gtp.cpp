#include "../ioc4.h"
#include "ioc4gtp.h"
#include "../luashell/iocLua.h"
#include "pv/timeStamp.h"
#include "pv/pvTimeStamp.h"


/**
 * This function is executed right before a record will initialized,
 * this is the last place where we can mutate the record structure.
 * In this function we check if records 'gtp' field exists, and if it does
 * we add appropriate timestamp fields to the fields specifed in 'gtp'
 */
PVStructurePtr ioc4gtp_mutateRecord(PVStructurePtr& record){
    const PVFieldPtrArray fields = record->getPVFields();

    //Check if "gtp" field exists
    PVStringPtr gtpField = dynamic_pointer_cast<PVString>(record->getSubField("gtp"));

    if(gtpField){
        //Gtp field exist, for each field specified [csv] add a new field with tst structure
        std::stringstream ss(gtpField->get());
        string fieldName;
        while(std::getline(ss,fieldName,',')){
            cout << "Mutating record to accomodate gtp" << fieldName << endl;
            //Change the original record
            record = PVDataLua::appendPVField(record,fieldName+"_timeStamp",getPVDataCreate()->createPVStructure(getStandardField()->timeStamp()));
        }
    }

    return record;
}
void ioc4gtp_bindToRecord(iocRecordPtr record){
    //Check if gtp field exists
    PVStringPtr gtpField = dynamic_pointer_cast<PVString>(record->getPVRecordStructure()->getPVStructure()->getSubField("gtp"));
    if(!gtpField) return;

    //Gtp field exist, for each field specified [csv] add a timestamp listener
    std::stringstream ss(gtpField->get());
    string fieldName;
    while(std::getline(ss,fieldName,',')){
        cout << "Binding gtp logic to " << record->getRecordName() << "." << fieldName << endl;

        PVRecordFieldPtr field = record->findPVRecordFieldByName(fieldName);
        PVStructurePtr field_timestamp = dynamic_pointer_cast<PVStructure>(
                    record->findPVRecordFieldByName(fieldName+"_timeStamp")->
                    getPVField());

        //Attach the code that will be executed within the handler (e.g. whenever a field specifed in [gtp]
        //will execute
        PVTimeStamp* pvT = new PVTimeStamp();
        if(!pvT->attach(field_timestamp)) throw runtime_error("Cannot attach to pvtimestamp");

        record->addFieldHandler(field,[pvT](PVRecordFieldPtr){
            TimeStamp t;
            t.getCurrent();
            pvT->set(t);
        });
    }

}

void register_ioc4gtp()
{
    ioc4::getIoc()->sig_recordAfterStaging += ioc4gtp_mutateRecord;
    ioc4::getIoc()->sig_recordInDatabase += ioc4gtp_bindToRecord;
}
