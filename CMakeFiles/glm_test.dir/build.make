# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/alice/Desktop/learn_opengl

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/alice/Desktop/learn_opengl

# Include any dependencies generated for this target.
include CMakeFiles/glm_test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/glm_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/glm_test.dir/flags.make

CMakeFiles/glm_test.dir/src/glm_test.cpp.o: CMakeFiles/glm_test.dir/flags.make
CMakeFiles/glm_test.dir/src/glm_test.cpp.o: src/glm_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alice/Desktop/learn_opengl/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/glm_test.dir/src/glm_test.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/glm_test.dir/src/glm_test.cpp.o -c /home/alice/Desktop/learn_opengl/src/glm_test.cpp

CMakeFiles/glm_test.dir/src/glm_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/glm_test.dir/src/glm_test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alice/Desktop/learn_opengl/src/glm_test.cpp > CMakeFiles/glm_test.dir/src/glm_test.cpp.i

CMakeFiles/glm_test.dir/src/glm_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/glm_test.dir/src/glm_test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alice/Desktop/learn_opengl/src/glm_test.cpp -o CMakeFiles/glm_test.dir/src/glm_test.cpp.s

CMakeFiles/glm_test.dir/src/glm_test.cpp.o.requires:

.PHONY : CMakeFiles/glm_test.dir/src/glm_test.cpp.o.requires

CMakeFiles/glm_test.dir/src/glm_test.cpp.o.provides: CMakeFiles/glm_test.dir/src/glm_test.cpp.o.requires
	$(MAKE) -f CMakeFiles/glm_test.dir/build.make CMakeFiles/glm_test.dir/src/glm_test.cpp.o.provides.build
.PHONY : CMakeFiles/glm_test.dir/src/glm_test.cpp.o.provides

CMakeFiles/glm_test.dir/src/glm_test.cpp.o.provides.build: CMakeFiles/glm_test.dir/src/glm_test.cpp.o


# Object files for target glm_test
glm_test_OBJECTS = \
"CMakeFiles/glm_test.dir/src/glm_test.cpp.o"

# External object files for target glm_test
glm_test_EXTERNAL_OBJECTS =

bin/glm_test: CMakeFiles/glm_test.dir/src/glm_test.cpp.o
bin/glm_test: CMakeFiles/glm_test.dir/build.make
bin/glm_test: CMakeFiles/glm_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/alice/Desktop/learn_opengl/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/glm_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/glm_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/glm_test.dir/build: bin/glm_test

.PHONY : CMakeFiles/glm_test.dir/build

CMakeFiles/glm_test.dir/requires: CMakeFiles/glm_test.dir/src/glm_test.cpp.o.requires

.PHONY : CMakeFiles/glm_test.dir/requires

CMakeFiles/glm_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/glm_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/glm_test.dir/clean

CMakeFiles/glm_test.dir/depend:
	cd /home/alice/Desktop/learn_opengl && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alice/Desktop/learn_opengl /home/alice/Desktop/learn_opengl /home/alice/Desktop/learn_opengl /home/alice/Desktop/learn_opengl /home/alice/Desktop/learn_opengl/CMakeFiles/glm_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/glm_test.dir/depend
