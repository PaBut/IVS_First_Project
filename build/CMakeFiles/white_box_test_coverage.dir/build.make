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
CMAKE_SOURCE_DIR = /home/pabut/IVS_Project1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pabut/IVS_Project1/build

# Utility rule file for white_box_test_coverage.

# Include any custom commands dependencies for this target.
include CMakeFiles/white_box_test_coverage.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/white_box_test_coverage.dir/progress.make

CMakeFiles/white_box_test_coverage:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/pabut/IVS_Project1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Resetting code coverage counters to zero."
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Processing code coverage counters and generating report."
	/usr/bin/lcov --directory . --zerocounters
	/home/pabut/IVS_Project1/build/white_box_test || ( exit 0 )
	/usr/bin/lcov --directory . --capture --output-file /home/pabut/IVS_Project1/build/white_box_test_coverage.info
	/usr/bin/lcov --remove /home/pabut/IVS_Project1/build/white_box_test_coverage.info '*_tests.cpp' '/usr/*' '*/googletest-*/*' --output-file /home/pabut/IVS_Project1/build/white_box_test_coverage.info.cleaned
	/usr/bin/genhtml -o white_box_test_coverage /home/pabut/IVS_Project1/build/white_box_test_coverage.info.cleaned
	/usr/bin/cmake -E remove /home/pabut/IVS_Project1/build/white_box_test_coverage.info /home/pabut/IVS_Project1/build/white_box_test_coverage.info.cleaned

white_box_test_coverage: CMakeFiles/white_box_test_coverage
white_box_test_coverage: CMakeFiles/white_box_test_coverage.dir/build.make
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Open ./white_box_test_coverage/index.html in your browser to view the coverage report."
.PHONY : white_box_test_coverage

# Rule to build all files generated by this target.
CMakeFiles/white_box_test_coverage.dir/build: white_box_test_coverage
.PHONY : CMakeFiles/white_box_test_coverage.dir/build

CMakeFiles/white_box_test_coverage.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/white_box_test_coverage.dir/cmake_clean.cmake
.PHONY : CMakeFiles/white_box_test_coverage.dir/clean

CMakeFiles/white_box_test_coverage.dir/depend:
	cd /home/pabut/IVS_Project1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pabut/IVS_Project1 /home/pabut/IVS_Project1 /home/pabut/IVS_Project1/build /home/pabut/IVS_Project1/build /home/pabut/IVS_Project1/build/CMakeFiles/white_box_test_coverage.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/white_box_test_coverage.dir/depend

