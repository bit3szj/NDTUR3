# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_SOURCE_DIR = /home/szj/myTask/test_link_UR/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/szj/myTask/test_link_UR/build

# Include any dependencies generated for this target.
include gravity_compensate/CMakeFiles/gravity_identify.dir/depend.make

# Include the progress variables for this target.
include gravity_compensate/CMakeFiles/gravity_identify.dir/progress.make

# Include the compile flags for this target's objects.
include gravity_compensate/CMakeFiles/gravity_identify.dir/flags.make

gravity_compensate/CMakeFiles/gravity_identify.dir/src/gravity_identify.cpp.o: gravity_compensate/CMakeFiles/gravity_identify.dir/flags.make
gravity_compensate/CMakeFiles/gravity_identify.dir/src/gravity_identify.cpp.o: /home/szj/myTask/test_link_UR/src/gravity_compensate/src/gravity_identify.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/szj/myTask/test_link_UR/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object gravity_compensate/CMakeFiles/gravity_identify.dir/src/gravity_identify.cpp.o"
	cd /home/szj/myTask/test_link_UR/build/gravity_compensate && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gravity_identify.dir/src/gravity_identify.cpp.o -c /home/szj/myTask/test_link_UR/src/gravity_compensate/src/gravity_identify.cpp

gravity_compensate/CMakeFiles/gravity_identify.dir/src/gravity_identify.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gravity_identify.dir/src/gravity_identify.cpp.i"
	cd /home/szj/myTask/test_link_UR/build/gravity_compensate && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/szj/myTask/test_link_UR/src/gravity_compensate/src/gravity_identify.cpp > CMakeFiles/gravity_identify.dir/src/gravity_identify.cpp.i

gravity_compensate/CMakeFiles/gravity_identify.dir/src/gravity_identify.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gravity_identify.dir/src/gravity_identify.cpp.s"
	cd /home/szj/myTask/test_link_UR/build/gravity_compensate && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/szj/myTask/test_link_UR/src/gravity_compensate/src/gravity_identify.cpp -o CMakeFiles/gravity_identify.dir/src/gravity_identify.cpp.s

# Object files for target gravity_identify
gravity_identify_OBJECTS = \
"CMakeFiles/gravity_identify.dir/src/gravity_identify.cpp.o"

# External object files for target gravity_identify
gravity_identify_EXTERNAL_OBJECTS =

/home/szj/myTask/test_link_UR/devel/lib/gravity_compensate/gravity_identify: gravity_compensate/CMakeFiles/gravity_identify.dir/src/gravity_identify.cpp.o
/home/szj/myTask/test_link_UR/devel/lib/gravity_compensate/gravity_identify: gravity_compensate/CMakeFiles/gravity_identify.dir/build.make
/home/szj/myTask/test_link_UR/devel/lib/gravity_compensate/gravity_identify: gravity_compensate/CMakeFiles/gravity_identify.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/szj/myTask/test_link_UR/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable /home/szj/myTask/test_link_UR/devel/lib/gravity_compensate/gravity_identify"
	cd /home/szj/myTask/test_link_UR/build/gravity_compensate && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gravity_identify.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
gravity_compensate/CMakeFiles/gravity_identify.dir/build: /home/szj/myTask/test_link_UR/devel/lib/gravity_compensate/gravity_identify

.PHONY : gravity_compensate/CMakeFiles/gravity_identify.dir/build

gravity_compensate/CMakeFiles/gravity_identify.dir/clean:
	cd /home/szj/myTask/test_link_UR/build/gravity_compensate && $(CMAKE_COMMAND) -P CMakeFiles/gravity_identify.dir/cmake_clean.cmake
.PHONY : gravity_compensate/CMakeFiles/gravity_identify.dir/clean

gravity_compensate/CMakeFiles/gravity_identify.dir/depend:
	cd /home/szj/myTask/test_link_UR/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/szj/myTask/test_link_UR/src /home/szj/myTask/test_link_UR/src/gravity_compensate /home/szj/myTask/test_link_UR/build /home/szj/myTask/test_link_UR/build/gravity_compensate /home/szj/myTask/test_link_UR/build/gravity_compensate/CMakeFiles/gravity_identify.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : gravity_compensate/CMakeFiles/gravity_identify.dir/depend

