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
include CMakeFiles/lighting.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/lighting.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/lighting.dir/flags.make

CMakeFiles/lighting.dir/src/lighting.cpp.o: CMakeFiles/lighting.dir/flags.make
CMakeFiles/lighting.dir/src/lighting.cpp.o: src/lighting.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alice/Desktop/learn_opengl/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/lighting.dir/src/lighting.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lighting.dir/src/lighting.cpp.o -c /home/alice/Desktop/learn_opengl/src/lighting.cpp

CMakeFiles/lighting.dir/src/lighting.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lighting.dir/src/lighting.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alice/Desktop/learn_opengl/src/lighting.cpp > CMakeFiles/lighting.dir/src/lighting.cpp.i

CMakeFiles/lighting.dir/src/lighting.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lighting.dir/src/lighting.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alice/Desktop/learn_opengl/src/lighting.cpp -o CMakeFiles/lighting.dir/src/lighting.cpp.s

CMakeFiles/lighting.dir/src/lighting.cpp.o.requires:

.PHONY : CMakeFiles/lighting.dir/src/lighting.cpp.o.requires

CMakeFiles/lighting.dir/src/lighting.cpp.o.provides: CMakeFiles/lighting.dir/src/lighting.cpp.o.requires
	$(MAKE) -f CMakeFiles/lighting.dir/build.make CMakeFiles/lighting.dir/src/lighting.cpp.o.provides.build
.PHONY : CMakeFiles/lighting.dir/src/lighting.cpp.o.provides

CMakeFiles/lighting.dir/src/lighting.cpp.o.provides.build: CMakeFiles/lighting.dir/src/lighting.cpp.o


CMakeFiles/lighting.dir/glad/src/glad.c.o: CMakeFiles/lighting.dir/flags.make
CMakeFiles/lighting.dir/glad/src/glad.c.o: glad/src/glad.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alice/Desktop/learn_opengl/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/lighting.dir/glad/src/glad.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/lighting.dir/glad/src/glad.c.o   -c /home/alice/Desktop/learn_opengl/glad/src/glad.c

CMakeFiles/lighting.dir/glad/src/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lighting.dir/glad/src/glad.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/alice/Desktop/learn_opengl/glad/src/glad.c > CMakeFiles/lighting.dir/glad/src/glad.c.i

CMakeFiles/lighting.dir/glad/src/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lighting.dir/glad/src/glad.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/alice/Desktop/learn_opengl/glad/src/glad.c -o CMakeFiles/lighting.dir/glad/src/glad.c.s

CMakeFiles/lighting.dir/glad/src/glad.c.o.requires:

.PHONY : CMakeFiles/lighting.dir/glad/src/glad.c.o.requires

CMakeFiles/lighting.dir/glad/src/glad.c.o.provides: CMakeFiles/lighting.dir/glad/src/glad.c.o.requires
	$(MAKE) -f CMakeFiles/lighting.dir/build.make CMakeFiles/lighting.dir/glad/src/glad.c.o.provides.build
.PHONY : CMakeFiles/lighting.dir/glad/src/glad.c.o.provides

CMakeFiles/lighting.dir/glad/src/glad.c.o.provides.build: CMakeFiles/lighting.dir/glad/src/glad.c.o


# Object files for target lighting
lighting_OBJECTS = \
"CMakeFiles/lighting.dir/src/lighting.cpp.o" \
"CMakeFiles/lighting.dir/glad/src/glad.c.o"

# External object files for target lighting
lighting_EXTERNAL_OBJECTS =

bin/lighting: CMakeFiles/lighting.dir/src/lighting.cpp.o
bin/lighting: CMakeFiles/lighting.dir/glad/src/glad.c.o
bin/lighting: CMakeFiles/lighting.dir/build.make
bin/lighting: CMakeFiles/lighting.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/alice/Desktop/learn_opengl/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable bin/lighting"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lighting.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/lighting.dir/build: bin/lighting

.PHONY : CMakeFiles/lighting.dir/build

CMakeFiles/lighting.dir/requires: CMakeFiles/lighting.dir/src/lighting.cpp.o.requires
CMakeFiles/lighting.dir/requires: CMakeFiles/lighting.dir/glad/src/glad.c.o.requires

.PHONY : CMakeFiles/lighting.dir/requires

CMakeFiles/lighting.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/lighting.dir/cmake_clean.cmake
.PHONY : CMakeFiles/lighting.dir/clean

CMakeFiles/lighting.dir/depend:
	cd /home/alice/Desktop/learn_opengl && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alice/Desktop/learn_opengl /home/alice/Desktop/learn_opengl /home/alice/Desktop/learn_opengl /home/alice/Desktop/learn_opengl /home/alice/Desktop/learn_opengl/CMakeFiles/lighting.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/lighting.dir/depend

