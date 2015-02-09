cmake_minimum_required (VERSION 2.6)
project (ioc4)

set(CMAKE_BUILD_TYPE Debug)

##Include a coitre for precompiled headers
set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/.")
include(cotire)




include_directories(/opt/epics/e4/pvDataCPP/include)
include_directories(/opt/epics/e4/pvDatabaseCPP/include)
include_directories(/opt/epics/e4/pvAccessCPP/include)
include_directories(/opt/epics/base/include)
include_directories(/opt/epics/base/include/os/Linux/)

link_directories(/opt/epics/base/lib/linux-x86_64)
link_directories(/opt/epics/e4/pvDataCPP/lib/linux-x86_64)
link_directories(/opt/epics/e4/pvDatabaseCPP/lib/linux-x86_64)
link_directories(/opt/epics/e4/pvAccessCPP/lib/linux-x86_64)

list( APPEND CMAKE_CXX_FLAGS "-std=c++11 -Wno-deprecated -g -finstrument-functions")
#list( APPEND CMAKE_CXX_FLAGS "")




add_library(ioc4  SHARED ioc4.cpp
                    pvutils.cpp
                    iocUtils.cpp
                    std/luaRecord.cpp
		    std/ioc4gtp.cpp
                    luashell/iocLua.cpp)

target_link_libraries(ioc4 pvData pvDatabase pvAccess Com lua5.2 luabind lttng-ust)
cotire(ioc4)



add_executable(tests tests.cpp )
target_link_libraries(tests ioc4)
cotire(tests)

add_library(ioclua SHARED luashell/iocLua.cpp)
target_link_libraries(ioclua ioc4 )
cotire(ioclua)

add_executable(queue_test queue.cpp)
target_link_libraries(queue_test Com)



