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
include CMakeFiles/tests_unity.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/tests_unity.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tests_unity.dir/flags.make

cotire/tests_CXX_unity.cxx: tests_CXX_cotire.cmake
	$(CMAKE_COMMAND) -E cmake_progress_report /home/tom/Git/projects/ioc4/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating CXX unity source cotire/tests_CXX_unity.cxx"
	cd /home/tom/Git/projects/ioc4 && /usr/bin/cmake -DCOTIRE_BUILD_TYPE:STRING= -DCOTIRE_VERBOSE:BOOL=$(VERBOSE) -P /home/tom/Git/projects/ioc4/cotire.cmake unity /home/tom/Git/projects/ioc4/build/tests_CXX_cotire.cmake /home/tom/Git/projects/ioc4/build/cotire/tests_CXX_unity.cxx

CMakeFiles/tests_unity.dir/cotire/tests_CXX_unity.cxx.o: CMakeFiles/tests_unity.dir/flags.make
CMakeFiles/tests_unity.dir/cotire/tests_CXX_unity.cxx.o: cotire/tests_CXX_unity.cxx
	$(CMAKE_COMMAND) -E cmake_progress_report /home/tom/Git/projects/ioc4/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/tests_unity.dir/cotire/tests_CXX_unity.cxx.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/tests_unity.dir/cotire/tests_CXX_unity.cxx.o -c /home/tom/Git/projects/ioc4/build/cotire/tests_CXX_unity.cxx

CMakeFiles/tests_unity.dir/cotire/tests_CXX_unity.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tests_unity.dir/cotire/tests_CXX_unity.cxx.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/tom/Git/projects/ioc4/build/cotire/tests_CXX_unity.cxx > CMakeFiles/tests_unity.dir/cotire/tests_CXX_unity.cxx.i

CMakeFiles/tests_unity.dir/cotire/tests_CXX_unity.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tests_unity.dir/cotire/tests_CXX_unity.cxx.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/tom/Git/projects/ioc4/build/cotire/tests_CXX_unity.cxx -o CMakeFiles/tests_unity.dir/cotire/tests_CXX_unity.cxx.s

CMakeFiles/tests_unity.dir/cotire/tests_CXX_unity.cxx.o.requires:
.PHONY : CMakeFiles/tests_unity.dir/cotire/tests_CXX_unity.cxx.o.requires

CMakeFiles/tests_unity.dir/cotire/tests_CXX_unity.cxx.o.provides: CMakeFiles/tests_unity.dir/cotire/tests_CXX_unity.cxx.o.requires
	$(MAKE) -f CMakeFiles/tests_unity.dir/build.make CMakeFiles/tests_unity.dir/cotire/tests_CXX_unity.cxx.o.provides.build
.PHONY : CMakeFiles/tests_unity.dir/cotire/tests_CXX_unity.cxx.o.provides

CMakeFiles/tests_unity.dir/cotire/tests_CXX_unity.cxx.o.provides.build: CMakeFiles/tests_unity.dir/cotire/tests_CXX_unity.cxx.o

# Object files for target tests_unity
tests_unity_OBJECTS = \
"CMakeFiles/tests_unity.dir/cotire/tests_CXX_unity.cxx.o"

# External object files for target tests_unity
tests_unity_EXTERNAL_OBJECTS =

tests: CMakeFiles/tests_unity.dir/cotire/tests_CXX_unity.cxx.o
tests: CMakeFiles/tests_unity.dir/build.make
tests: CMakeFiles/tests_unity.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable tests"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tests_unity.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tests_unity.dir/build: tests
.PHONY : CMakeFiles/tests_unity.dir/build

CMakeFiles/tests_unity.dir/requires: CMakeFiles/tests_unity.dir/cotire/tests_CXX_unity.cxx.o.requires
.PHONY : CMakeFiles/tests_unity.dir/requires

CMakeFiles/tests_unity.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tests_unity.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tests_unity.dir/clean

CMakeFiles/tests_unity.dir/depend: cotire/tests_CXX_unity.cxx
	cd /home/tom/Git/projects/ioc4/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tom/Git/projects/ioc4 /home/tom/Git/projects/ioc4 /home/tom/Git/projects/ioc4/build /home/tom/Git/projects/ioc4/build /home/tom/Git/projects/ioc4/build/CMakeFiles/tests_unity.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tests_unity.dir/depend

