# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.31

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
CMAKE_COMMAND = /opt/homebrew/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/ala.biezychudek/Code/zendesk/AbstraC/UrbanMotion

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/ala.biezychudek/Code/zendesk/AbstraC/UrbanMotion/build

# Include any dependencies generated for this target.
include _deps/glfw-build/tests/CMakeFiles/tearing.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include _deps/glfw-build/tests/CMakeFiles/tearing.dir/compiler_depend.make

# Include the progress variables for this target.
include _deps/glfw-build/tests/CMakeFiles/tearing.dir/progress.make

# Include the compile flags for this target's objects.
include _deps/glfw-build/tests/CMakeFiles/tearing.dir/flags.make

_deps/glfw-build/tests/CMakeFiles/tearing.dir/codegen:
.PHONY : _deps/glfw-build/tests/CMakeFiles/tearing.dir/codegen

_deps/glfw-build/tests/CMakeFiles/tearing.dir/tearing.c.o: _deps/glfw-build/tests/CMakeFiles/tearing.dir/flags.make
_deps/glfw-build/tests/CMakeFiles/tearing.dir/tearing.c.o: _deps/glfw-src/tests/tearing.c
_deps/glfw-build/tests/CMakeFiles/tearing.dir/tearing.c.o: _deps/glfw-build/tests/CMakeFiles/tearing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/ala.biezychudek/Code/zendesk/AbstraC/UrbanMotion/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object _deps/glfw-build/tests/CMakeFiles/tearing.dir/tearing.c.o"
	cd /Users/ala.biezychudek/Code/zendesk/AbstraC/UrbanMotion/build/_deps/glfw-build/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT _deps/glfw-build/tests/CMakeFiles/tearing.dir/tearing.c.o -MF CMakeFiles/tearing.dir/tearing.c.o.d -o CMakeFiles/tearing.dir/tearing.c.o -c /Users/ala.biezychudek/Code/zendesk/AbstraC/UrbanMotion/build/_deps/glfw-src/tests/tearing.c

_deps/glfw-build/tests/CMakeFiles/tearing.dir/tearing.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/tearing.dir/tearing.c.i"
	cd /Users/ala.biezychudek/Code/zendesk/AbstraC/UrbanMotion/build/_deps/glfw-build/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ala.biezychudek/Code/zendesk/AbstraC/UrbanMotion/build/_deps/glfw-src/tests/tearing.c > CMakeFiles/tearing.dir/tearing.c.i

_deps/glfw-build/tests/CMakeFiles/tearing.dir/tearing.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/tearing.dir/tearing.c.s"
	cd /Users/ala.biezychudek/Code/zendesk/AbstraC/UrbanMotion/build/_deps/glfw-build/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ala.biezychudek/Code/zendesk/AbstraC/UrbanMotion/build/_deps/glfw-src/tests/tearing.c -o CMakeFiles/tearing.dir/tearing.c.s

_deps/glfw-build/tests/CMakeFiles/tearing.dir/__/deps/glad_gl.c.o: _deps/glfw-build/tests/CMakeFiles/tearing.dir/flags.make
_deps/glfw-build/tests/CMakeFiles/tearing.dir/__/deps/glad_gl.c.o: _deps/glfw-src/deps/glad_gl.c
_deps/glfw-build/tests/CMakeFiles/tearing.dir/__/deps/glad_gl.c.o: _deps/glfw-build/tests/CMakeFiles/tearing.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/ala.biezychudek/Code/zendesk/AbstraC/UrbanMotion/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object _deps/glfw-build/tests/CMakeFiles/tearing.dir/__/deps/glad_gl.c.o"
	cd /Users/ala.biezychudek/Code/zendesk/AbstraC/UrbanMotion/build/_deps/glfw-build/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT _deps/glfw-build/tests/CMakeFiles/tearing.dir/__/deps/glad_gl.c.o -MF CMakeFiles/tearing.dir/__/deps/glad_gl.c.o.d -o CMakeFiles/tearing.dir/__/deps/glad_gl.c.o -c /Users/ala.biezychudek/Code/zendesk/AbstraC/UrbanMotion/build/_deps/glfw-src/deps/glad_gl.c

_deps/glfw-build/tests/CMakeFiles/tearing.dir/__/deps/glad_gl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/tearing.dir/__/deps/glad_gl.c.i"
	cd /Users/ala.biezychudek/Code/zendesk/AbstraC/UrbanMotion/build/_deps/glfw-build/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ala.biezychudek/Code/zendesk/AbstraC/UrbanMotion/build/_deps/glfw-src/deps/glad_gl.c > CMakeFiles/tearing.dir/__/deps/glad_gl.c.i

_deps/glfw-build/tests/CMakeFiles/tearing.dir/__/deps/glad_gl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/tearing.dir/__/deps/glad_gl.c.s"
	cd /Users/ala.biezychudek/Code/zendesk/AbstraC/UrbanMotion/build/_deps/glfw-build/tests && /Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ala.biezychudek/Code/zendesk/AbstraC/UrbanMotion/build/_deps/glfw-src/deps/glad_gl.c -o CMakeFiles/tearing.dir/__/deps/glad_gl.c.s

# Object files for target tearing
tearing_OBJECTS = \
"CMakeFiles/tearing.dir/tearing.c.o" \
"CMakeFiles/tearing.dir/__/deps/glad_gl.c.o"

# External object files for target tearing
tearing_EXTERNAL_OBJECTS =

_deps/glfw-build/tests/tearing.app/Contents/MacOS/tearing: _deps/glfw-build/tests/CMakeFiles/tearing.dir/tearing.c.o
_deps/glfw-build/tests/tearing.app/Contents/MacOS/tearing: _deps/glfw-build/tests/CMakeFiles/tearing.dir/__/deps/glad_gl.c.o
_deps/glfw-build/tests/tearing.app/Contents/MacOS/tearing: _deps/glfw-build/tests/CMakeFiles/tearing.dir/build.make
_deps/glfw-build/tests/tearing.app/Contents/MacOS/tearing: _deps/glfw-build/src/libglfw3.a
_deps/glfw-build/tests/tearing.app/Contents/MacOS/tearing: _deps/glfw-build/tests/CMakeFiles/tearing.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/ala.biezychudek/Code/zendesk/AbstraC/UrbanMotion/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable tearing.app/Contents/MacOS/tearing"
	cd /Users/ala.biezychudek/Code/zendesk/AbstraC/UrbanMotion/build/_deps/glfw-build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tearing.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
_deps/glfw-build/tests/CMakeFiles/tearing.dir/build: _deps/glfw-build/tests/tearing.app/Contents/MacOS/tearing
.PHONY : _deps/glfw-build/tests/CMakeFiles/tearing.dir/build

_deps/glfw-build/tests/CMakeFiles/tearing.dir/clean:
	cd /Users/ala.biezychudek/Code/zendesk/AbstraC/UrbanMotion/build/_deps/glfw-build/tests && $(CMAKE_COMMAND) -P CMakeFiles/tearing.dir/cmake_clean.cmake
.PHONY : _deps/glfw-build/tests/CMakeFiles/tearing.dir/clean

_deps/glfw-build/tests/CMakeFiles/tearing.dir/depend:
	cd /Users/ala.biezychudek/Code/zendesk/AbstraC/UrbanMotion/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/ala.biezychudek/Code/zendesk/AbstraC/UrbanMotion /Users/ala.biezychudek/Code/zendesk/AbstraC/UrbanMotion/build/_deps/glfw-src/tests /Users/ala.biezychudek/Code/zendesk/AbstraC/UrbanMotion/build /Users/ala.biezychudek/Code/zendesk/AbstraC/UrbanMotion/build/_deps/glfw-build/tests /Users/ala.biezychudek/Code/zendesk/AbstraC/UrbanMotion/build/_deps/glfw-build/tests/CMakeFiles/tearing.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : _deps/glfw-build/tests/CMakeFiles/tearing.dir/depend

