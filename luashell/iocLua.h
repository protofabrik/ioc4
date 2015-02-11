#include <iostream>


#include <pv/pvData.h>
#include <lua.hpp>

using namespace epics::pvData;
using namespace std;

class PVDataLua{
public:


    /**
     * @brief PVStructureToLua, pushes PVStructure of any type onto lua stack
     * @param L
     * @param pv_struct
     */
    static void PVStructureToLua(lua_State* L, PVStructurePtr pv_struct);

    /**
     * @brief appendPVField
     * Brute-force method of mutating shape of PVStructures. On append, a new structure with additional field is created,
     * than a deep copy is preformed from original structure.
     * @param orig
     * @param name
     * @param field
     * @return A new pvStructure
     */
    static PVStructurePtr appendPVField(PVStructurePtr orig,string name, PVFieldPtr field);

    static PVStructurePtr luaToNewPVStructure(lua_State* L);

    inline static void luaToPVStructure(lua_State *L, PVStructurePtr structure){
        luaToPVStructure(L,structure.get());
    }

private:
    static void luaToPVStructure(lua_State *L, PVStructure* structure);
};

