# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/faber/software-udvikling/Lektion5_test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/faber/software-udvikling/Lektion5_test/build

# Include any dependencies generated for this target.
include CMakeFiles/MainTest.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/MainTest.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/MainTest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MainTest.dir/flags.make

CMakeFiles/MainTest.dir/main.cpp.o: CMakeFiles/MainTest.dir/flags.make
CMakeFiles/MainTest.dir/main.cpp.o: ../main.cpp
CMakeFiles/MainTest.dir/main.cpp.o: CMakeFiles/MainTest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/faber/software-udvikling/Lektion5_test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/MainTest.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/MainTest.dir/main.cpp.o -MF CMakeFiles/MainTest.dir/main.cpp.o.d -o CMakeFiles/MainTest.dir/main.cpp.o -c /home/faber/software-udvikling/Lektion5_test/main.cpp

CMakeFiles/MainTest.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/MainTest.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/faber/software-udvikling/Lektion5_test/main.cpp > CMakeFiles/MainTest.dir/main.cpp.i

CMakeFiles/MainTest.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/MainTest.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/faber/software-udvikling/Lektion5_test/main.cpp -o CMakeFiles/MainTest.dir/main.cpp.s

# Object files for target MainTest
MainTest_OBJECTS = \
"CMakeFiles/MainTest.dir/main.cpp.o"

# External object files for target MainTest
MainTest_EXTERNAL_OBJECTS =

MainTest: CMakeFiles/MainTest.dir/main.cpp.o
MainTest: CMakeFiles/MainTest.dir/build.make
MainTest: /usr/lib/x86_64-linux-gnu/libQt5Sql.so.5.15.3
MainTest: /usr/lib/x86_64-linux-gnu/libQt5Core.so.5.15.3
MainTest: CMakeFiles/MainTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/faber/software-udvikling/Lektion5_test/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable MainTest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MainTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MainTest.dir/build: MainTest
.PHONY : CMakeFiles/MainTest.dir/build

CMakeFiles/MainTest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MainTest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MainTest.dir/clean

CMakeFiles/MainTest.dir/depend:
	cd /home/faber/software-udvikling/Lektion5_test/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/faber/software-udvikling/Lektion5_test /home/faber/software-udvikling/Lektion5_test /home/faber/software-udvikling/Lektion5_test/build /home/faber/software-udvikling/Lektion5_test/build /home/faber/software-udvikling/Lektion5_test/build/CMakeFiles/MainTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MainTest.dir/depend

