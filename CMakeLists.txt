cmake_minimum_required (VERSION 2.6)
project (ioc4)

set(CMAKE_BUILD_TYPE Debug)


include_directories(/opt/epics/e4/pvDataCPP/include)
include_directories(/opt/epics/e4/pvDatabaseCPP/include)
include_directories(/opt/epics/e4/pvAccessCPP/include)
include_directories(/opt/epics/base/include)
include_directories(/opt/epics/base/include/os/Linux/)

link_directories(/opt/epics/base/lib/linux-x86_64)
link_directories(/opt/epics/e4/pvDataCPP/lib/linux-x86_64)
link_directories(/opt/epics/e4/pvDatabaseCPP/lib/linux-x86_64)
link_directories(/opt/epics/e4/pvAccessCPP/lib/linux-x86_64)

list( APPEND CMAKE_CXX_FLAGS "-std=c++11 -Wno-deprecated")
#list( APPEND CMAKE_CXX_FLAGS "")



#add_executable(pvDataTest pvDataTest.cpp)
add_executable(ioc4 ioc4.cpp
                    tests.cpp
                    pvutils.cpp)

#target_link_libraries(pvDataTest pvData Com)
target_link_libraries(ioc4 pvData pvDatabase pvAccess Com)



