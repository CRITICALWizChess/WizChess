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
CMAKE_SOURCE_DIR = D:\WizChess\MotorTest_XInC2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\WizChess\MotorTest_XInC2\build

# Include any dependencies generated for this target.
include CMakeFiles/motortest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/motortest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/motortest.dir/flags.make

CMakeFiles/motortest.dir/src/main.cpp.obj: CMakeFiles/motortest.dir/flags.make
CMakeFiles/motortest.dir/src/main.cpp.obj: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\WizChess\MotorTest_XInC2\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/motortest.dir/src/main.cpp.obj"
	D:\SXC\bin\sxc-none-eabi-clang++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\motortest.dir\src\main.cpp.obj -c D:\WizChess\MotorTest_XInC2\src\main.cpp

CMakeFiles/motortest.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/motortest.dir/src/main.cpp.i"
	$(CMAKE_COMMAND) -E cmake_unimplemented_variable CMAKE_CXX_CREATE_PREPROCESSED_SOURCE

CMakeFiles/motortest.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/motortest.dir/src/main.cpp.s"
	$(CMAKE_COMMAND) -E cmake_unimplemented_variable CMAKE_CXX_CREATE_ASSEMBLY_SOURCE

# Object files for target motortest
motortest_OBJECTS = \
"CMakeFiles/motortest.dir/src/main.cpp.obj"

# External object files for target motortest
motortest_EXTERNAL_OBJECTS =

motortest.a: CMakeFiles/motortest.dir/src/main.cpp.obj
motortest.a: CMakeFiles/motortest.dir/build.make
motortest.a: D:/SXC/lib/sxc-none-eabi/sxc-crt0.a
motortest.a: CMakeFiles/motortest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\WizChess\MotorTest_XInC2\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable motortest.a"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\motortest.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/motortest.dir/build: motortest.a

.PHONY : CMakeFiles/motortest.dir/build

CMakeFiles/motortest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\motortest.dir\cmake_clean.cmake
.PHONY : CMakeFiles/motortest.dir/clean

CMakeFiles/motortest.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\WizChess\MotorTest_XInC2 D:\WizChess\MotorTest_XInC2 D:\WizChess\MotorTest_XInC2\build D:\WizChess\MotorTest_XInC2\build D:\WizChess\MotorTest_XInC2\build\CMakeFiles\motortest.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/motortest.dir/depend

