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

# Utility rule file for ioc4_pch.

# Include the progress variables for this target.
include CMakeFiles/ioc4_pch.dir/progress.make

CMakeFiles/ioc4_pch: cotire/ioc4_CXX_prefix.hxx.gch

cotire/ioc4_CXX_prefix.hxx.gch: cotire/ioc4_CXX_prefix.hxx
cotire/ioc4_CXX_prefix.hxx.gch: cotire/ioc4_CXX_prefix.hxx
	$(CMAKE_COMMAND) -E cmake_progress_report /home/tom/Git/projects/ioc4/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Building CXX precompiled header cotire/ioc4_CXX_prefix.hxx.gch"
	cd /home/tom/Git/projects/ioc4 && /usr/bin/cmake -DCOTIRE_BUILD_TYPE:STRING= -DCOTIRE_VERBOSE:BOOL=$(VERBOSE) -P /home/tom/Git/projects/ioc4/cotire.cmake precompile /home/tom/Git/projects/ioc4/build/ioc4_CXX_cotire.cmake /home/tom/Git/projects/ioc4/build/cotire/ioc4_CXX_prefix.hxx /home/tom/Git/projects/ioc4/build/cotire/ioc4_CXX_prefix.hxx.gch ioc4.cpp

cotire/ioc4_CXX_prefix.hxx: cotire/ioc4_CXX_prefix.cxx
	$(CMAKE_COMMAND) -E cmake_progress_report /home/tom/Git/projects/ioc4/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating CXX prefix header cotire/ioc4_CXX_prefix.hxx"
	cd /home/tom/Git/projects/ioc4 && /usr/bin/cmake -DCOTIRE_BUILD_TYPE:STRING= -DCOTIRE_VERBOSE:BOOL=$(VERBOSE) -P /home/tom/Git/projects/ioc4/cotire.cmake combine /home/tom/Git/projects/ioc4/build/ioc4_CXX_cotire.cmake /home/tom/Git/projects/ioc4/build/cotire/ioc4_CXX_prefix.hxx build/cotire/ioc4_CXX_prefix.cxx

cotire/ioc4_CXX_prefix.cxx: cotire/ioc4_CXX_unity.cxx
	$(CMAKE_COMMAND) -E cmake_progress_report /home/tom/Git/projects/ioc4/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating CXX prefix source cotire/ioc4_CXX_prefix.cxx"
	/usr/bin/cmake -DCOTIRE_BUILD_TYPE:STRING= -DCOTIRE_VERBOSE:BOOL=$(VERBOSE) -P /home/tom/Git/projects/ioc4/cotire.cmake prefix /home/tom/Git/projects/ioc4/build/ioc4_CXX_cotire.cmake /home/tom/Git/projects/ioc4/build/cotire/ioc4_CXX_prefix.cxx /home/tom/Git/projects/ioc4/build/cotire/ioc4_CXX_unity.cxx

cotire/ioc4_CXX_prefix.cxx.log: cotire/ioc4_CXX_prefix.cxx

cotire/ioc4_CXX_unity.cxx: ioc4_CXX_cotire.cmake
	$(CMAKE_COMMAND) -E cmake_progress_report /home/tom/Git/projects/ioc4/build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating CXX unity source cotire/ioc4_CXX_unity.cxx"
	cd /home/tom/Git/projects/ioc4 && /usr/bin/cmake -DCOTIRE_BUILD_TYPE:STRING= -DCOTIRE_VERBOSE:BOOL=$(VERBOSE) -P /home/tom/Git/projects/ioc4/cotire.cmake unity /home/tom/Git/projects/ioc4/build/ioc4_CXX_cotire.cmake /home/tom/Git/projects/ioc4/build/cotire/ioc4_CXX_unity.cxx

ioc4_pch: CMakeFiles/ioc4_pch
ioc4_pch: cotire/ioc4_CXX_prefix.hxx.gch
ioc4_pch: cotire/ioc4_CXX_prefix.hxx
ioc4_pch: cotire/ioc4_CXX_prefix.cxx
ioc4_pch: cotire/ioc4_CXX_prefix.cxx.log
ioc4_pch: cotire/ioc4_CXX_unity.cxx
ioc4_pch: CMakeFiles/ioc4_pch.dir/build.make
.PHONY : ioc4_pch

# Rule to build all files generated by this target.
CMakeFiles/ioc4_pch.dir/build: ioc4_pch
.PHONY : CMakeFiles/ioc4_pch.dir/build

CMakeFiles/ioc4_pch.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ioc4_pch.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ioc4_pch.dir/clean

CMakeFiles/ioc4_pch.dir/depend:
	cd /home/tom/Git/projects/ioc4/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tom/Git/projects/ioc4 /home/tom/Git/projects/ioc4 /home/tom/Git/projects/ioc4/build /home/tom/Git/projects/ioc4/build /home/tom/Git/projects/ioc4/build/CMakeFiles/ioc4_pch.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ioc4_pch.dir/depend

