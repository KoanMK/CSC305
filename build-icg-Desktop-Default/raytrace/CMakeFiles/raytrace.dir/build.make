# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.3

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.3.1/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.3.1/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/nigeld/Desktop/icg

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/nigeld/Desktop/build-icg-Desktop-Default

# Include any dependencies generated for this target.
include raytrace/CMakeFiles/raytrace.dir/depend.make

# Include the progress variables for this target.
include raytrace/CMakeFiles/raytrace.dir/progress.make

# Include the compile flags for this target's objects.
include raytrace/CMakeFiles/raytrace.dir/flags.make

raytrace/CMakeFiles/raytrace.dir/main.cpp.o: raytrace/CMakeFiles/raytrace.dir/flags.make
raytrace/CMakeFiles/raytrace.dir/main.cpp.o: /Users/nigeld/Desktop/icg/raytrace/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/nigeld/Desktop/build-icg-Desktop-Default/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object raytrace/CMakeFiles/raytrace.dir/main.cpp.o"
	cd /Users/nigeld/Desktop/build-icg-Desktop-Default/raytrace && /usr/bin/g++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/raytrace.dir/main.cpp.o -c /Users/nigeld/Desktop/icg/raytrace/main.cpp

raytrace/CMakeFiles/raytrace.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/raytrace.dir/main.cpp.i"
	cd /Users/nigeld/Desktop/build-icg-Desktop-Default/raytrace && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -E /Users/nigeld/Desktop/icg/raytrace/main.cpp > CMakeFiles/raytrace.dir/main.cpp.i

raytrace/CMakeFiles/raytrace.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/raytrace.dir/main.cpp.s"
	cd /Users/nigeld/Desktop/build-icg-Desktop-Default/raytrace && /usr/bin/g++  $(CXX_DEFINES) $(CXX_FLAGS) -S /Users/nigeld/Desktop/icg/raytrace/main.cpp -o CMakeFiles/raytrace.dir/main.cpp.s

raytrace/CMakeFiles/raytrace.dir/main.cpp.o.requires:

.PHONY : raytrace/CMakeFiles/raytrace.dir/main.cpp.o.requires

raytrace/CMakeFiles/raytrace.dir/main.cpp.o.provides: raytrace/CMakeFiles/raytrace.dir/main.cpp.o.requires
	$(MAKE) -f raytrace/CMakeFiles/raytrace.dir/build.make raytrace/CMakeFiles/raytrace.dir/main.cpp.o.provides.build
.PHONY : raytrace/CMakeFiles/raytrace.dir/main.cpp.o.provides

raytrace/CMakeFiles/raytrace.dir/main.cpp.o.provides.build: raytrace/CMakeFiles/raytrace.dir/main.cpp.o


# Object files for target raytrace
raytrace_OBJECTS = \
"CMakeFiles/raytrace.dir/main.cpp.o"

# External object files for target raytrace
raytrace_EXTERNAL_OBJECTS =

raytrace/raytrace: raytrace/CMakeFiles/raytrace.dir/main.cpp.o
raytrace/raytrace: raytrace/CMakeFiles/raytrace.dir/build.make
raytrace/raytrace: /usr/local/lib/libGLEW.dylib
raytrace/raytrace: /usr/local/lib/libglfw3.dylib
raytrace/raytrace: raytrace/CMakeFiles/raytrace.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/nigeld/Desktop/build-icg-Desktop-Default/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable raytrace"
	cd /Users/nigeld/Desktop/build-icg-Desktop-Default/raytrace && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/raytrace.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
raytrace/CMakeFiles/raytrace.dir/build: raytrace/raytrace

.PHONY : raytrace/CMakeFiles/raytrace.dir/build

raytrace/CMakeFiles/raytrace.dir/requires: raytrace/CMakeFiles/raytrace.dir/main.cpp.o.requires

.PHONY : raytrace/CMakeFiles/raytrace.dir/requires

raytrace/CMakeFiles/raytrace.dir/clean:
	cd /Users/nigeld/Desktop/build-icg-Desktop-Default/raytrace && $(CMAKE_COMMAND) -P CMakeFiles/raytrace.dir/cmake_clean.cmake
.PHONY : raytrace/CMakeFiles/raytrace.dir/clean

raytrace/CMakeFiles/raytrace.dir/depend:
	cd /Users/nigeld/Desktop/build-icg-Desktop-Default && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/nigeld/Desktop/icg /Users/nigeld/Desktop/icg/raytrace /Users/nigeld/Desktop/build-icg-Desktop-Default /Users/nigeld/Desktop/build-icg-Desktop-Default/raytrace /Users/nigeld/Desktop/build-icg-Desktop-Default/raytrace/CMakeFiles/raytrace.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : raytrace/CMakeFiles/raytrace.dir/depend

