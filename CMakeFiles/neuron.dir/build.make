# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.2

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/INTRANET/mghali/myfiles/ba3/neuron/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/INTRANET/mghali/myfiles/ba3/neuron

# Include any dependencies generated for this target.
include CMakeFiles/Neuron.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Neuron.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Neuron.dir/flags.make

CMakeFiles/Neuron.dir/neuron_main.cpp.o: CMakeFiles/Neuron.dir/flags.make
CMakeFiles/Neuron.dir/neuron_main.cpp.o: src/neuron_main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/INTRANET/mghali/myfiles/ba3/neuron/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Neuron.dir/neuron_main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Neuron.dir/neuron_main.cpp.o -c /home/INTRANET/mghali/myfiles/ba3/neuron/src/neuron_main.cpp

CMakeFiles/Neuron.dir/neuron_main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Neuron.dir/neuron_main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/INTRANET/mghali/myfiles/ba3/neuron/src/neuron_main.cpp > CMakeFiles/Neuron.dir/neuron_main.cpp.i

CMakeFiles/Neuron.dir/neuron_main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Neuron.dir/neuron_main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/INTRANET/mghali/myfiles/ba3/neuron/src/neuron_main.cpp -o CMakeFiles/Neuron.dir/neuron_main.cpp.s

CMakeFiles/Neuron.dir/neuron_main.cpp.o.requires:
.PHONY : CMakeFiles/Neuron.dir/neuron_main.cpp.o.requires

CMakeFiles/Neuron.dir/neuron_main.cpp.o.provides: CMakeFiles/Neuron.dir/neuron_main.cpp.o.requires
	$(MAKE) -f CMakeFiles/Neuron.dir/build.make CMakeFiles/Neuron.dir/neuron_main.cpp.o.provides.build
.PHONY : CMakeFiles/Neuron.dir/neuron_main.cpp.o.provides

CMakeFiles/Neuron.dir/neuron_main.cpp.o.provides.build: CMakeFiles/Neuron.dir/neuron_main.cpp.o

CMakeFiles/Neuron.dir/network.cpp.o: CMakeFiles/Neuron.dir/flags.make
CMakeFiles/Neuron.dir/network.cpp.o: src/network.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/INTRANET/mghali/myfiles/ba3/neuron/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Neuron.dir/network.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Neuron.dir/network.cpp.o -c /home/INTRANET/mghali/myfiles/ba3/neuron/src/network.cpp

CMakeFiles/Neuron.dir/network.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Neuron.dir/network.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/INTRANET/mghali/myfiles/ba3/neuron/src/network.cpp > CMakeFiles/Neuron.dir/network.cpp.i

CMakeFiles/Neuron.dir/network.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Neuron.dir/network.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/INTRANET/mghali/myfiles/ba3/neuron/src/network.cpp -o CMakeFiles/Neuron.dir/network.cpp.s

CMakeFiles/Neuron.dir/network.cpp.o.requires:
.PHONY : CMakeFiles/Neuron.dir/network.cpp.o.requires

CMakeFiles/Neuron.dir/network.cpp.o.provides: CMakeFiles/Neuron.dir/network.cpp.o.requires
	$(MAKE) -f CMakeFiles/Neuron.dir/build.make CMakeFiles/Neuron.dir/network.cpp.o.provides.build
.PHONY : CMakeFiles/Neuron.dir/network.cpp.o.provides

CMakeFiles/Neuron.dir/network.cpp.o.provides.build: CMakeFiles/Neuron.dir/network.cpp.o

CMakeFiles/Neuron.dir/neuron.cpp.o: CMakeFiles/Neuron.dir/flags.make
CMakeFiles/Neuron.dir/neuron.cpp.o: src/neuron.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/INTRANET/mghali/myfiles/ba3/neuron/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/Neuron.dir/neuron.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/Neuron.dir/neuron.cpp.o -c /home/INTRANET/mghali/myfiles/ba3/neuron/src/neuron.cpp

CMakeFiles/Neuron.dir/neuron.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Neuron.dir/neuron.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/INTRANET/mghali/myfiles/ba3/neuron/src/neuron.cpp > CMakeFiles/Neuron.dir/neuron.cpp.i

CMakeFiles/Neuron.dir/neuron.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Neuron.dir/neuron.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/INTRANET/mghali/myfiles/ba3/neuron/src/neuron.cpp -o CMakeFiles/Neuron.dir/neuron.cpp.s

CMakeFiles/Neuron.dir/neuron.cpp.o.requires:
.PHONY : CMakeFiles/Neuron.dir/neuron.cpp.o.requires

CMakeFiles/Neuron.dir/neuron.cpp.o.provides: CMakeFiles/Neuron.dir/neuron.cpp.o.requires
	$(MAKE) -f CMakeFiles/Neuron.dir/build.make CMakeFiles/Neuron.dir/neuron.cpp.o.provides.build
.PHONY : CMakeFiles/Neuron.dir/neuron.cpp.o.provides

CMakeFiles/Neuron.dir/neuron.cpp.o.provides.build: CMakeFiles/Neuron.dir/neuron.cpp.o

# Object files for target Neuron
Neuron_OBJECTS = \
"CMakeFiles/Neuron.dir/neuron_main.cpp.o" \
"CMakeFiles/Neuron.dir/network.cpp.o" \
"CMakeFiles/Neuron.dir/neuron.cpp.o"

# External object files for target Neuron
Neuron_EXTERNAL_OBJECTS =

Neuron: CMakeFiles/Neuron.dir/neuron_main.cpp.o
Neuron: CMakeFiles/Neuron.dir/network.cpp.o
Neuron: CMakeFiles/Neuron.dir/neuron.cpp.o
Neuron: CMakeFiles/Neuron.dir/build.make
Neuron: CMakeFiles/Neuron.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable Neuron"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Neuron.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Neuron.dir/build: Neuron
.PHONY : CMakeFiles/Neuron.dir/build

CMakeFiles/Neuron.dir/requires: CMakeFiles/Neuron.dir/neuron_main.cpp.o.requires
CMakeFiles/Neuron.dir/requires: CMakeFiles/Neuron.dir/network.cpp.o.requires
CMakeFiles/Neuron.dir/requires: CMakeFiles/Neuron.dir/neuron.cpp.o.requires
.PHONY : CMakeFiles/Neuron.dir/requires

CMakeFiles/Neuron.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Neuron.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Neuron.dir/clean

CMakeFiles/Neuron.dir/depend:
	cd /home/INTRANET/mghali/myfiles/ba3/neuron && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/INTRANET/mghali/myfiles/ba3/neuron/src /home/INTRANET/mghali/myfiles/ba3/neuron/src /home/INTRANET/mghali/myfiles/ba3/neuron /home/INTRANET/mghali/myfiles/ba3/neuron /home/INTRANET/mghali/myfiles/ba3/neuron/CMakeFiles/Neuron.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Neuron.dir/depend

