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

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/rafa/Downloads/myro-cpp-2.3.0

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/rafa/Downloads/myro-cpp-2.3.0/build

# Include any dependencies generated for this target.
include test/graphics/CMakeFiles/myro_graphwin_test.dir/depend.make

# Include the progress variables for this target.
include test/graphics/CMakeFiles/myro_graphwin_test.dir/progress.make

# Include the compile flags for this target's objects.
include test/graphics/CMakeFiles/myro_graphwin_test.dir/flags.make

test/graphics/CMakeFiles/myro_graphwin_test.dir/graphwin_test.cpp.o: test/graphics/CMakeFiles/myro_graphwin_test.dir/flags.make
test/graphics/CMakeFiles/myro_graphwin_test.dir/graphwin_test.cpp.o: ../test/graphics/graphwin_test.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/rafa/Downloads/myro-cpp-2.3.0/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object test/graphics/CMakeFiles/myro_graphwin_test.dir/graphwin_test.cpp.o"
	cd /home/rafa/Downloads/myro-cpp-2.3.0/build/test/graphics && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/myro_graphwin_test.dir/graphwin_test.cpp.o -c /home/rafa/Downloads/myro-cpp-2.3.0/test/graphics/graphwin_test.cpp

test/graphics/CMakeFiles/myro_graphwin_test.dir/graphwin_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/myro_graphwin_test.dir/graphwin_test.cpp.i"
	cd /home/rafa/Downloads/myro-cpp-2.3.0/build/test/graphics && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/rafa/Downloads/myro-cpp-2.3.0/test/graphics/graphwin_test.cpp > CMakeFiles/myro_graphwin_test.dir/graphwin_test.cpp.i

test/graphics/CMakeFiles/myro_graphwin_test.dir/graphwin_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/myro_graphwin_test.dir/graphwin_test.cpp.s"
	cd /home/rafa/Downloads/myro-cpp-2.3.0/build/test/graphics && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/rafa/Downloads/myro-cpp-2.3.0/test/graphics/graphwin_test.cpp -o CMakeFiles/myro_graphwin_test.dir/graphwin_test.cpp.s

test/graphics/CMakeFiles/myro_graphwin_test.dir/graphwin_test.cpp.o.requires:
.PHONY : test/graphics/CMakeFiles/myro_graphwin_test.dir/graphwin_test.cpp.o.requires

test/graphics/CMakeFiles/myro_graphwin_test.dir/graphwin_test.cpp.o.provides: test/graphics/CMakeFiles/myro_graphwin_test.dir/graphwin_test.cpp.o.requires
	$(MAKE) -f test/graphics/CMakeFiles/myro_graphwin_test.dir/build.make test/graphics/CMakeFiles/myro_graphwin_test.dir/graphwin_test.cpp.o.provides.build
.PHONY : test/graphics/CMakeFiles/myro_graphwin_test.dir/graphwin_test.cpp.o.provides

test/graphics/CMakeFiles/myro_graphwin_test.dir/graphwin_test.cpp.o.provides.build: test/graphics/CMakeFiles/myro_graphwin_test.dir/graphwin_test.cpp.o

# Object files for target myro_graphwin_test
myro_graphwin_test_OBJECTS = \
"CMakeFiles/myro_graphwin_test.dir/graphwin_test.cpp.o"

# External object files for target myro_graphwin_test
myro_graphwin_test_EXTERNAL_OBJECTS =

test/graphics/myro_graphwin_test: test/graphics/CMakeFiles/myro_graphwin_test.dir/graphwin_test.cpp.o
test/graphics/myro_graphwin_test: src/libmyro-cpp.so.2.3.0
test/graphics/myro_graphwin_test: src/libmyro-cpp.so.2.3.0
test/graphics/myro_graphwin_test: /usr/lib/libSM.so
test/graphics/myro_graphwin_test: /usr/lib/libICE.so
test/graphics/myro_graphwin_test: /usr/lib/i386-linux-gnu/libX11.so
test/graphics/myro_graphwin_test: /usr/lib/libXext.so
test/graphics/myro_graphwin_test: jpeg/libmyrocpp_jpeg.a
test/graphics/myro_graphwin_test: test/graphics/CMakeFiles/myro_graphwin_test.dir/build.make
test/graphics/myro_graphwin_test: test/graphics/CMakeFiles/myro_graphwin_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable myro_graphwin_test"
	cd /home/rafa/Downloads/myro-cpp-2.3.0/build/test/graphics && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/myro_graphwin_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/graphics/CMakeFiles/myro_graphwin_test.dir/build: test/graphics/myro_graphwin_test
.PHONY : test/graphics/CMakeFiles/myro_graphwin_test.dir/build

test/graphics/CMakeFiles/myro_graphwin_test.dir/requires: test/graphics/CMakeFiles/myro_graphwin_test.dir/graphwin_test.cpp.o.requires
.PHONY : test/graphics/CMakeFiles/myro_graphwin_test.dir/requires

test/graphics/CMakeFiles/myro_graphwin_test.dir/clean:
	cd /home/rafa/Downloads/myro-cpp-2.3.0/build/test/graphics && $(CMAKE_COMMAND) -P CMakeFiles/myro_graphwin_test.dir/cmake_clean.cmake
.PHONY : test/graphics/CMakeFiles/myro_graphwin_test.dir/clean

test/graphics/CMakeFiles/myro_graphwin_test.dir/depend:
	cd /home/rafa/Downloads/myro-cpp-2.3.0/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/rafa/Downloads/myro-cpp-2.3.0 /home/rafa/Downloads/myro-cpp-2.3.0/test/graphics /home/rafa/Downloads/myro-cpp-2.3.0/build /home/rafa/Downloads/myro-cpp-2.3.0/build/test/graphics /home/rafa/Downloads/myro-cpp-2.3.0/build/test/graphics/CMakeFiles/myro_graphwin_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/graphics/CMakeFiles/myro_graphwin_test.dir/depend

