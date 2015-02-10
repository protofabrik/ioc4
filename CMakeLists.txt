cmake_minimum_required (VERSION 2.6)
project (ioc4)

#set(CMAKE_BUILD_TYPE Debug)

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

#list( APPEND CMAKE_CXX_FLAGS "-std=c++11 -Wno-deprecated -g -finstrument-functions")
list( APPEND CMAKE_CXX_FLAGS "-std=c++11 -Wno-deprecated -O3")


######## MAIN IOC4 LIBRARY
add_library(ioc4  SHARED ioc4.cpp
                    pvutils.cpp
                    iocUtils.cpp
                    std/luaRecord.cpp
                    std/ioc4gtp.cpp
                    luashell/iocLua.cpp
                    utils/pvFastCopy.cpp
                    )


target_link_libraries(ioc4 pvData pvDatabase pvAccess Com lua5.2 luabind lttng-ust)
#cotire(ioc4)

## INSTALL HEADERS
add_custom_command(TARGET ioc4 PRE_BUILD COMMAND cp ${CMAKE_SOURCE_DIR}/ioc4.h $<TARGET_FILE_DIR:ioc4>/include)
add_custom_command(TARGET ioc4 PRE_BUILD COMMAND cp ${CMAKE_SOURCE_DIR}/simplesignal.h $<TARGET_FILE_DIR:ioc4>/include)
add_custom_command(TARGET ioc4 PRE_BUILD COMMAND cp ${CMAKE_SOURCE_DIR}/pvutils.h $<TARGET_FILE_DIR:ioc4>/include)
add_custom_command(TARGET ioc4 PRE_BUILD COMMAND cp ${CMAKE_SOURCE_DIR}/utils/pvFastCopy.h $<TARGET_FILE_DIR:ioc4>/include/utils/)
add_custom_command(TARGET ioc4 PRE_BUILD COMMAND cp ${CMAKE_SOURCE_DIR}/std/standardRecords.h $<TARGET_FILE_DIR:ioc4>/include)


## Test application

add_executable(tests tests.cpp )
target_link_libraries(tests ioc4)


add_library(ioclua SHARED luashell/iocLua.cpp)
target_link_libraries(ioclua ioc4 )


#add_executable(queue_test queue.cpp)
#target_link_libraries(queue_test Com)

#list( REPLACE CMAKE_CXX_FLAGS "-std=c++11 -O3")

include_directories(build/include)
add_executable(tests_copy tests/tests_copy.cpp)
target_link_libraries(tests_copy ioc4 pvData pvDatabase pvAccess Com)


include_directories(build/include)
add_executable(tests_perf_syn tests/tests_perf_syn.cpp)
target_link_libraries(tests_perf_syn ioc4)



