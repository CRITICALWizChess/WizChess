# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.12

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = D:\CMake\bin\cmake.exe

# The command to remove a file.
RM = D:\CMake\bin\cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Documents\motorTest_V2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Documents\motorTest_V2\build

# Utility rule file for MotorTest2-s.

# Include the progress variables for this target.
include CMakeFiles/MotorTest2-s.dir/progress.make

CMakeFiles/MotorTest2-s: MotorTest2.s


MotorTest2.s: MotorTest2.opt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=D:\Documents\motorTest_V2\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating MotorTest2.s"
	D:\SXC\bin\sxc-none-eabi-llc.exe D:/Documents/motorTest_V2/build/MotorTest2.opt -O3 -o D:/Documents/motorTest_V2/build/MotorTest2.s

MotorTest2.opt: MotorTest2.a
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=D:\Documents\motorTest_V2\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Generating MotorTest2.opt"
	D:\SXC\bin\sxc-none-eabi-opt.exe D:/Documents/motorTest_V2/build/MotorTest2.a -o D:/Documents/motorTest_V2/build/MotorTest2.opt -O3 -std-link-opts -loweratomic -unroll-threshold 20 -inline-threshold 15

MotorTest2-s: CMakeFiles/MotorTest2-s
MotorTest2-s: MotorTest2.s
MotorTest2-s: MotorTest2.opt
MotorTest2-s: CMakeFiles/MotorTest2-s.dir/build.make

.PHONY : MotorTest2-s

# Rule to build all files generated by this target.
CMakeFiles/MotorTest2-s.dir/build: MotorTest2-s

.PHONY : CMakeFiles/MotorTest2-s.dir/build

CMakeFiles/MotorTest2-s.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\MotorTest2-s.dir\cmake_clean.cmake
.PHONY : CMakeFiles/MotorTest2-s.dir/clean

CMakeFiles/MotorTest2-s.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Documents\motorTest_V2 D:\Documents\motorTest_V2 D:\Documents\motorTest_V2\build D:\Documents\motorTest_V2\build D:\Documents\motorTest_V2\build\CMakeFiles\MotorTest2-s.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MotorTest2-s.dir/depend

