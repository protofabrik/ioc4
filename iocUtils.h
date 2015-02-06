#include "ioc4.h"


class proxyListner : public PVListener{
public:

    proxyListner(function<void(PVRecordFieldPtr)> dataPutListner):
                putListner(dataPutListner)
    {

    }

    static PVListenerPtr l(function<void(PVRecordFieldPtr)> dataPutListner){
        return PVListenerPtr(new proxyListner(dataPutListner));
    }

private:

    function<void(PVRecordFieldPtr)> putListner;
    function<void(PVFieldPtr)> beginGroupPutListner;
    function<void(PVFieldPtr)> endGroupPutListner;


    void dataPut(PVRecordFieldPtr const & pvRecordField){
        putListner(pvRecordField);
    }

    void dataPut(PVRecordStructurePtr const & requested,
                 PVRecordFieldPtr const & pvRecordField){
        putListner(requested);
    }



    virtual void beginGroupPut(PVRecordPtr const & pvRecord){
        CALLTRACE
    }

    virtual void endGroupPut(PVRecordPtr const & pvRecord){CALLTRACE}

    virtual void unlisten(PVRecordPtr const & pvRecord){CALLTRACE}

    virtual void detach(PVRecordPtr const & pvRecord){CALLTRACE}

};



class iocUtils{

public:
    static void printDatabase(std::ostream& o){
        PVDatabasePtr db = PVDatabase::getMaster();
        PVStringArray::const_svector recordNames;

        db->getRecordNames()->getAs(recordNames);

        vector<iocRecordPtr> records;

        for(string s : recordNames){
            iocRecordPtr record = ioc4::getIoc()->findRecord(s);

            o << "RECORD: "<< record->getRecordName() <<endl;
            record->getPVRecordStructure()->getPVField()->dumpValue(o);
            o << endl;
        }
    }

    static void printDatabaseNames(std::ostream& o){
        PVDatabasePtr db = PVDatabase::getMaster();
        PVStringArray::const_svector recordNames;

        db->getRecordNames()->getAs(recordNames);

        vector<iocRecordPtr> records;

        for(string s : recordNames){
            o << "RECORD: "<< s <<endl;
        }
    }

    static void monitorField(string fieldName, std::ostream& o){
        PVRecordFieldPtr field = ioc4::getIoc()->findField(fieldName);

        PVListenerPtr listner = proxyListner::l([](PVRecordFieldPtr field){
                string buf;
                getConvert()->getString(&buf,field->getPVField());
                cout << field->getFullName() << " : " << buf;
            });

        field->addListener(listner);
    }
};

