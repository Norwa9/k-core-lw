# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/luowei/Desktop/k-cores20201218/loadDataTest

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/luowei/Desktop/k-cores20201218/loadDataTest/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/loadDataTest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/loadDataTest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/loadDataTest.dir/flags.make

CMakeFiles/loadDataTest.dir/main.cpp.o: CMakeFiles/loadDataTest.dir/flags.make
CMakeFiles/loadDataTest.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/luowei/Desktop/k-cores20201218/loadDataTest/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/loadDataTest.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/loadDataTest.dir/main.cpp.o -c /Users/luowei/Desktop/k-cores20201218/loadDataTest/main.cpp

CMakeFiles/loadDataTest.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/loadDataTest.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/luowei/Desktop/k-cores20201218/loadDataTest/main.cpp > CMakeFiles/loadDataTest.dir/main.cpp.i

CMakeFiles/loadDataTest.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/loadDataTest.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/luowei/Desktop/k-cores20201218/loadDataTest/main.cpp -o CMakeFiles/loadDataTest.dir/main.cpp.s

# Object files for target loadDataTest
loadDataTest_OBJECTS = \
"CMakeFiles/loadDataTest.dir/main.cpp.o"

# External object files for target loadDataTest
loadDataTest_EXTERNAL_OBJECTS =

loadDataTest: CMakeFiles/loadDataTest.dir/main.cpp.o
loadDataTest: CMakeFiles/loadDataTest.dir/build.make
loadDataTest: CMakeFiles/loadDataTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/luowei/Desktop/k-cores20201218/loadDataTest/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable loadDataTest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/loadDataTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/loadDataTest.dir/build: loadDataTest

.PHONY : CMakeFiles/loadDataTest.dir/build

CMakeFiles/loadDataTest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/loadDataTest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/loadDataTest.dir/clean

CMakeFiles/loadDataTest.dir/depend:
	cd /Users/luowei/Desktop/k-cores20201218/loadDataTest/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/luowei/Desktop/k-cores20201218/loadDataTest /Users/luowei/Desktop/k-cores20201218/loadDataTest /Users/luowei/Desktop/k-cores20201218/loadDataTest/cmake-build-debug /Users/luowei/Desktop/k-cores20201218/loadDataTest/cmake-build-debug /Users/luowei/Desktop/k-cores20201218/loadDataTest/cmake-build-debug/CMakeFiles/loadDataTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/loadDataTest.dir/depend

