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
include test/CMakeFiles/askQuestion.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/askQuestion.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/askQuestion.dir/flags.make

test/CMakeFiles/askQuestion.dir/askQuestion.cpp.o: test/CMakeFiles/askQuestion.dir/flags.make
test/CMakeFiles/askQuestion.dir/askQuestion.cpp.o: ../test/askQuestion.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/rafa/Downloads/myro-cpp-2.3.0/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object test/CMakeFiles/askQuestion.dir/askQuestion.cpp.o"
	cd /home/rafa/Downloads/myro-cpp-2.3.0/build/test && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/askQuestion.dir/askQuestion.cpp.o -c /home/rafa/Downloads/myro-cpp-2.3.0/test/askQuestion.cpp

test/CMakeFiles/askQuestion.dir/askQuestion.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/askQuestion.dir/askQuestion.cpp.i"
	cd /home/rafa/Downloads/myro-cpp-2.3.0/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/rafa/Downloads/myro-cpp-2.3.0/test/askQuestion.cpp > CMakeFiles/askQuestion.dir/askQuestion.cpp.i

test/CMakeFiles/askQuestion.dir/askQuestion.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/askQuestion.dir/askQuestion.cpp.s"
	cd /home/rafa/Downloads/myro-cpp-2.3.0/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/rafa/Downloads/myro-cpp-2.3.0/test/askQuestion.cpp -o CMakeFiles/askQuestion.dir/askQuestion.cpp.s

test/CMakeFiles/askQuestion.dir/askQuestion.cpp.o.requires:
.PHONY : test/CMakeFiles/askQuestion.dir/askQuestion.cpp.o.requires

test/CMakeFiles/askQuestion.dir/askQuestion.cpp.o.provides: test/CMakeFiles/askQuestion.dir/askQuestion.cpp.o.requires
	$(MAKE) -f test/CMakeFiles/askQuestion.dir/build.make test/CMakeFiles/askQuestion.dir/askQuestion.cpp.o.provides.build
.PHONY : test/CMakeFiles/askQuestion.dir/askQuestion.cpp.o.provides

test/CMakeFiles/askQuestion.dir/askQuestion.cpp.o.provides.build: test/CMakeFiles/askQuestion.dir/askQuestion.cpp.o

# Object files for target askQuestion
askQuestion_OBJECTS = \
"CMakeFiles/askQuestion.dir/askQuestion.cpp.o"

# External object files for target askQuestion
askQuestion_EXTERNAL_OBJECTS =

test/askQuestion: test/CMakeFiles/askQuestion.dir/askQuestion.cpp.o
test/askQuestion: src/libmyro-cpp.so.2.3.0
test/askQuestion: /usr/lib/libSM.so
test/askQuestion: /usr/lib/libICE.so
test/askQuestion: /usr/lib/i386-linux-gnu/libX11.so
test/askQuestion: /usr/lib/libXext.so
test/askQuestion: jpeg/libmyrocpp_jpeg.a
test/askQuestion: test/CMakeFiles/askQuestion.dir/build.make
test/askQuestion: test/CMakeFiles/askQuestion.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable askQuestion"
	cd /home/rafa/Downloads/myro-cpp-2.3.0/build/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/askQuestion.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/askQuestion.dir/build: test/askQuestion
.PHONY : test/CMakeFiles/askQuestion.dir/build

test/CMakeFiles/askQuestion.dir/requires: test/CMakeFiles/askQuestion.dir/askQuestion.cpp.o.requires
.PHONY : test/CMakeFiles/askQuestion.dir/requires

test/CMakeFiles/askQuestion.dir/clean:
	cd /home/rafa/Downloads/myro-cpp-2.3.0/build/test && $(CMAKE_COMMAND) -P CMakeFiles/askQuestion.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/askQuestion.dir/clean

test/CMakeFiles/askQuestion.dir/depend:
	cd /home/rafa/Downloads/myro-cpp-2.3.0/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/rafa/Downloads/myro-cpp-2.3.0 /home/rafa/Downloads/myro-cpp-2.3.0/test /home/rafa/Downloads/myro-cpp-2.3.0/build /home/rafa/Downloads/myro-cpp-2.3.0/build/test /home/rafa/Downloads/myro-cpp-2.3.0/build/test/CMakeFiles/askQuestion.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/askQuestion.dir/depend

