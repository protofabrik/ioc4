# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/tom/Git/projects/ioc4

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tom/Git/projects/ioc4/build

# Include any dependencies generated for this target.
include CMakeFiles/ioc4.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ioc4.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ioc4.dir/flags.make

CMakeFiles/ioc4.dir/ioc4.cpp.o: CMakeFiles/ioc4.dir/flags.make
CMakeFiles/ioc4.dir/ioc4.cpp.o: ../ioc4.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/tom/Git/projects/ioc4/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/ioc4.dir/ioc4.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ioc4.dir/ioc4.cpp.o -c /home/tom/Git/projects/ioc4/ioc4.cpp

CMakeFiles/ioc4.dir/ioc4.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ioc4.dir/ioc4.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/tom/Git/projects/ioc4/ioc4.cpp > CMakeFiles/ioc4.dir/ioc4.cpp.i

CMakeFiles/ioc4.dir/ioc4.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ioc4.dir/ioc4.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/tom/Git/projects/ioc4/ioc4.cpp -o CMakeFiles/ioc4.dir/ioc4.cpp.s

CMakeFiles/ioc4.dir/ioc4.cpp.o.requires:
.PHONY : CMakeFiles/ioc4.dir/ioc4.cpp.o.requires

CMakeFiles/ioc4.dir/ioc4.cpp.o.provides: CMakeFiles/ioc4.dir/ioc4.cpp.o.requires
	$(MAKE) -f CMakeFiles/ioc4.dir/build.make CMakeFiles/ioc4.dir/ioc4.cpp.o.provides.build
.PHONY : CMakeFiles/ioc4.dir/ioc4.cpp.o.provides

CMakeFiles/ioc4.dir/ioc4.cpp.o.provides.build: CMakeFiles/ioc4.dir/ioc4.cpp.o

CMakeFiles/ioc4.dir/pvutils.cpp.o: CMakeFiles/ioc4.dir/flags.make
CMakeFiles/ioc4.dir/pvutils.cpp.o: ../pvutils.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/tom/Git/projects/ioc4/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/ioc4.dir/pvutils.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ioc4.dir/pvutils.cpp.o -c /home/tom/Git/projects/ioc4/pvutils.cpp

CMakeFiles/ioc4.dir/pvutils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ioc4.dir/pvutils.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/tom/Git/projects/ioc4/pvutils.cpp > CMakeFiles/ioc4.dir/pvutils.cpp.i

CMakeFiles/ioc4.dir/pvutils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ioc4.dir/pvutils.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/tom/Git/projects/ioc4/pvutils.cpp -o CMakeFiles/ioc4.dir/pvutils.cpp.s

CMakeFiles/ioc4.dir/pvutils.cpp.o.requires:
.PHONY : CMakeFiles/ioc4.dir/pvutils.cpp.o.requires

CMakeFiles/ioc4.dir/pvutils.cpp.o.provides: CMakeFiles/ioc4.dir/pvutils.cpp.o.requires
	$(MAKE) -f CMakeFiles/ioc4.dir/build.make CMakeFiles/ioc4.dir/pvutils.cpp.o.provides.build
.PHONY : CMakeFiles/ioc4.dir/pvutils.cpp.o.provides

CMakeFiles/ioc4.dir/pvutils.cpp.o.provides.build: CMakeFiles/ioc4.dir/pvutils.cpp.o

CMakeFiles/ioc4.dir/iocUtils.cpp.o: CMakeFiles/ioc4.dir/flags.make
CMakeFiles/ioc4.dir/iocUtils.cpp.o: ../iocUtils.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/tom/Git/projects/ioc4/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/ioc4.dir/iocUtils.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ioc4.dir/iocUtils.cpp.o -c /home/tom/Git/projects/ioc4/iocUtils.cpp

CMakeFiles/ioc4.dir/iocUtils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ioc4.dir/iocUtils.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/tom/Git/projects/ioc4/iocUtils.cpp > CMakeFiles/ioc4.dir/iocUtils.cpp.i

CMakeFiles/ioc4.dir/iocUtils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ioc4.dir/iocUtils.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/tom/Git/projects/ioc4/iocUtils.cpp -o CMakeFiles/ioc4.dir/iocUtils.cpp.s

CMakeFiles/ioc4.dir/iocUtils.cpp.o.requires:
.PHONY : CMakeFiles/ioc4.dir/iocUtils.cpp.o.requires

CMakeFiles/ioc4.dir/iocUtils.cpp.o.provides: CMakeFiles/ioc4.dir/iocUtils.cpp.o.requires
	$(MAKE) -f CMakeFiles/ioc4.dir/build.make CMakeFiles/ioc4.dir/iocUtils.cpp.o.provides.build
.PHONY : CMakeFiles/ioc4.dir/iocUtils.cpp.o.provides

CMakeFiles/ioc4.dir/iocUtils.cpp.o.provides.build: CMakeFiles/ioc4.dir/iocUtils.cpp.o

CMakeFiles/ioc4.dir/std/luaRecord.cpp.o: CMakeFiles/ioc4.dir/flags.make
CMakeFiles/ioc4.dir/std/luaRecord.cpp.o: ../std/luaRecord.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/tom/Git/projects/ioc4/build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/ioc4.dir/std/luaRecord.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ioc4.dir/std/luaRecord.cpp.o -c /home/tom/Git/projects/ioc4/std/luaRecord.cpp

CMakeFiles/ioc4.dir/std/luaRecord.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ioc4.dir/std/luaRecord.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/tom/Git/projects/ioc4/std/luaRecord.cpp > CMakeFiles/ioc4.dir/std/luaRecord.cpp.i

CMakeFiles/ioc4.dir/std/luaRecord.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ioc4.dir/std/luaRecord.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/tom/Git/projects/ioc4/std/luaRecord.cpp -o CMakeFiles/ioc4.dir/std/luaRecord.cpp.s

CMakeFiles/ioc4.dir/std/luaRecord.cpp.o.requires:
.PHONY : CMakeFiles/ioc4.dir/std/luaRecord.cpp.o.requires

CMakeFiles/ioc4.dir/std/luaRecord.cpp.o.provides: CMakeFiles/ioc4.dir/std/luaRecord.cpp.o.requires
	$(MAKE) -f CMakeFiles/ioc4.dir/build.make CMakeFiles/ioc4.dir/std/luaRecord.cpp.o.provides.build
.PHONY : CMakeFiles/ioc4.dir/std/luaRecord.cpp.o.provides

CMakeFiles/ioc4.dir/std/luaRecord.cpp.o.provides.build: CMakeFiles/ioc4.dir/std/luaRecord.cpp.o

CMakeFiles/ioc4.dir/std/ioc4gtp.cpp.o: CMakeFiles/ioc4.dir/flags.make
CMakeFiles/ioc4.dir/std/ioc4gtp.cpp.o: ../std/ioc4gtp.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/tom/Git/projects/ioc4/build/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/ioc4.dir/std/ioc4gtp.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ioc4.dir/std/ioc4gtp.cpp.o -c /home/tom/Git/projects/ioc4/std/ioc4gtp.cpp

CMakeFiles/ioc4.dir/std/ioc4gtp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ioc4.dir/std/ioc4gtp.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/tom/Git/projects/ioc4/std/ioc4gtp.cpp > CMakeFiles/ioc4.dir/std/ioc4gtp.cpp.i

CMakeFiles/ioc4.dir/std/ioc4gtp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ioc4.dir/std/ioc4gtp.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/tom/Git/projects/ioc4/std/ioc4gtp.cpp -o CMakeFiles/ioc4.dir/std/ioc4gtp.cpp.s

CMakeFiles/ioc4.dir/std/ioc4gtp.cpp.o.requires:
.PHONY : CMakeFiles/ioc4.dir/std/ioc4gtp.cpp.o.requires

CMakeFiles/ioc4.dir/std/ioc4gtp.cpp.o.provides: CMakeFiles/ioc4.dir/std/ioc4gtp.cpp.o.requires
	$(MAKE) -f CMakeFiles/ioc4.dir/build.make CMakeFiles/ioc4.dir/std/ioc4gtp.cpp.o.provides.build
.PHONY : CMakeFiles/ioc4.dir/std/ioc4gtp.cpp.o.provides

CMakeFiles/ioc4.dir/std/ioc4gtp.cpp.o.provides.build: CMakeFiles/ioc4.dir/std/ioc4gtp.cpp.o

CMakeFiles/ioc4.dir/luashell/iocLua.cpp.o: CMakeFiles/ioc4.dir/flags.make
CMakeFiles/ioc4.dir/luashell/iocLua.cpp.o: ../luashell/iocLua.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/tom/Git/projects/ioc4/build/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/ioc4.dir/luashell/iocLua.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ioc4.dir/luashell/iocLua.cpp.o -c /home/tom/Git/projects/ioc4/luashell/iocLua.cpp

CMakeFiles/ioc4.dir/luashell/iocLua.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ioc4.dir/luashell/iocLua.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/tom/Git/projects/ioc4/luashell/iocLua.cpp > CMakeFiles/ioc4.dir/luashell/iocLua.cpp.i

CMakeFiles/ioc4.dir/luashell/iocLua.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ioc4.dir/luashell/iocLua.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/tom/Git/projects/ioc4/luashell/iocLua.cpp -o CMakeFiles/ioc4.dir/luashell/iocLua.cpp.s

CMakeFiles/ioc4.dir/luashell/iocLua.cpp.o.requires:
.PHONY : CMakeFiles/ioc4.dir/luashell/iocLua.cpp.o.requires

CMakeFiles/ioc4.dir/luashell/iocLua.cpp.o.provides: CMakeFiles/ioc4.dir/luashell/iocLua.cpp.o.requires
	$(MAKE) -f CMakeFiles/ioc4.dir/build.make CMakeFiles/ioc4.dir/luashell/iocLua.cpp.o.provides.build
.PHONY : CMakeFiles/ioc4.dir/luashell/iocLua.cpp.o.provides

CMakeFiles/ioc4.dir/luashell/iocLua.cpp.o.provides.build: CMakeFiles/ioc4.dir/luashell/iocLua.cpp.o

CMakeFiles/ioc4.dir/utils/pvFastCopy.cpp.o: CMakeFiles/ioc4.dir/flags.make
CMakeFiles/ioc4.dir/utils/pvFastCopy.cpp.o: ../utils/pvFastCopy.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/tom/Git/projects/ioc4/build/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/ioc4.dir/utils/pvFastCopy.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ioc4.dir/utils/pvFastCopy.cpp.o -c /home/tom/Git/projects/ioc4/utils/pvFastCopy.cpp

CMakeFiles/ioc4.dir/utils/pvFastCopy.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ioc4.dir/utils/pvFastCopy.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/tom/Git/projects/ioc4/utils/pvFastCopy.cpp > CMakeFiles/ioc4.dir/utils/pvFastCopy.cpp.i

CMakeFiles/ioc4.dir/utils/pvFastCopy.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ioc4.dir/utils/pvFastCopy.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/tom/Git/projects/ioc4/utils/pvFastCopy.cpp -o CMakeFiles/ioc4.dir/utils/pvFastCopy.cpp.s

CMakeFiles/ioc4.dir/utils/pvFastCopy.cpp.o.requires:
.PHONY : CMakeFiles/ioc4.dir/utils/pvFastCopy.cpp.o.requires

CMakeFiles/ioc4.dir/utils/pvFastCopy.cpp.o.provides: CMakeFiles/ioc4.dir/utils/pvFastCopy.cpp.o.requires
	$(MAKE) -f CMakeFiles/ioc4.dir/build.make CMakeFiles/ioc4.dir/utils/pvFastCopy.cpp.o.provides.build
.PHONY : CMakeFiles/ioc4.dir/utils/pvFastCopy.cpp.o.provides

CMakeFiles/ioc4.dir/utils/pvFastCopy.cpp.o.provides.build: CMakeFiles/ioc4.dir/utils/pvFastCopy.cpp.o

# Object files for target ioc4
ioc4_OBJECTS = \
"CMakeFiles/ioc4.dir/ioc4.cpp.o" \
"CMakeFiles/ioc4.dir/pvutils.cpp.o" \
"CMakeFiles/ioc4.dir/iocUtils.cpp.o" \
"CMakeFiles/ioc4.dir/std/luaRecord.cpp.o" \
"CMakeFiles/ioc4.dir/std/ioc4gtp.cpp.o" \
"CMakeFiles/ioc4.dir/luashell/iocLua.cpp.o" \
"CMakeFiles/ioc4.dir/utils/pvFastCopy.cpp.o"

# External object files for target ioc4
ioc4_EXTERNAL_OBJECTS =

libioc4.so: CMakeFiles/ioc4.dir/ioc4.cpp.o
libioc4.so: CMakeFiles/ioc4.dir/pvutils.cpp.o
libioc4.so: CMakeFiles/ioc4.dir/iocUtils.cpp.o
libioc4.so: CMakeFiles/ioc4.dir/std/luaRecord.cpp.o
libioc4.so: CMakeFiles/ioc4.dir/std/ioc4gtp.cpp.o
libioc4.so: CMakeFiles/ioc4.dir/luashell/iocLua.cpp.o
libioc4.so: CMakeFiles/ioc4.dir/utils/pvFastCopy.cpp.o
libioc4.so: CMakeFiles/ioc4.dir/build.make
libioc4.so: CMakeFiles/ioc4.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared library libioc4.so"
	cp /home/tom/Git/projects/ioc4/ioc4.h /home/tom/Git/projects/ioc4/build/include
	cp /home/tom/Git/projects/ioc4/simplesignal.h /home/tom/Git/projects/ioc4/build/include
	cp /home/tom/Git/projects/ioc4/pvutils.h /home/tom/Git/projects/ioc4/build/include
	cp /home/tom/Git/projects/ioc4/utils/pvFastCopy.h /home/tom/Git/projects/ioc4/build/include/utils/
	cp /home/tom/Git/projects/ioc4/std/standardRecords.h /home/tom/Git/projects/ioc4/build/include
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ioc4.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ioc4.dir/build: libioc4.so
.PHONY : CMakeFiles/ioc4.dir/build

CMakeFiles/ioc4.dir/requires: CMakeFiles/ioc4.dir/ioc4.cpp.o.requires
CMakeFiles/ioc4.dir/requires: CMakeFiles/ioc4.dir/pvutils.cpp.o.requires
CMakeFiles/ioc4.dir/requires: CMakeFiles/ioc4.dir/iocUtils.cpp.o.requires
CMakeFiles/ioc4.dir/requires: CMakeFiles/ioc4.dir/std/luaRecord.cpp.o.requires
CMakeFiles/ioc4.dir/requires: CMakeFiles/ioc4.dir/std/ioc4gtp.cpp.o.requires
CMakeFiles/ioc4.dir/requires: CMakeFiles/ioc4.dir/luashell/iocLua.cpp.o.requires
CMakeFiles/ioc4.dir/requires: CMakeFiles/ioc4.dir/utils/pvFastCopy.cpp.o.requires
.PHONY : CMakeFiles/ioc4.dir/requires

CMakeFiles/ioc4.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ioc4.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ioc4.dir/clean

CMakeFiles/ioc4.dir/depend:
	cd /home/tom/Git/projects/ioc4/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tom/Git/projects/ioc4 /home/tom/Git/projects/ioc4 /home/tom/Git/projects/ioc4/build /home/tom/Git/projects/ioc4/build /home/tom/Git/projects/ioc4/build/CMakeFiles/ioc4.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ioc4.dir/depend

