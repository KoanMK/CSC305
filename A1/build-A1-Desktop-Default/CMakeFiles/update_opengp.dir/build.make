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
CMAKE_SOURCE_DIR = /Users/nigeld/Desktop/V00853112/A1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/nigeld/Desktop/A1/build-A1-Desktop-Default

# Utility rule file for update_opengp.

# Include the progress variables for this target.
include CMakeFiles/update_opengp.dir/progress.make

CMakeFiles/update_opengp:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/nigeld/Desktop/A1/build-A1-Desktop-Default/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Updating OpenGP /Users/nigeld/Desktop/V00853112/A1"
	cd /Users/nigeld/Desktop/V00853112/A1/external/OpenGP/include && rm -rf OpenGP
	cd /Users/nigeld/Desktop/V00853112/A1/external/OpenGP/include && svn checkout https://github.com/OpenGP/OpenGP/trunk/src/OpenGP
	cd /Users/nigeld/Desktop/V00853112/A1/external/OpenGP/include && rm -rf OpenGP/.svn

update_opengp: CMakeFiles/update_opengp
update_opengp: CMakeFiles/update_opengp.dir/build.make

.PHONY : update_opengp

# Rule to build all files generated by this target.
CMakeFiles/update_opengp.dir/build: update_opengp

.PHONY : CMakeFiles/update_opengp.dir/build

CMakeFiles/update_opengp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/update_opengp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/update_opengp.dir/clean

CMakeFiles/update_opengp.dir/depend:
	cd /Users/nigeld/Desktop/A1/build-A1-Desktop-Default && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/nigeld/Desktop/V00853112/A1 /Users/nigeld/Desktop/V00853112/A1 /Users/nigeld/Desktop/A1/build-A1-Desktop-Default /Users/nigeld/Desktop/A1/build-A1-Desktop-Default /Users/nigeld/Desktop/A1/build-A1-Desktop-Default/CMakeFiles/update_opengp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/update_opengp.dir/depend

