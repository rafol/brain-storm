# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/rafol/Desktop/PCC/contagotas

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/rafol/Desktop/PCC/contagotas

# Include any dependencies generated for this target.
include CMakeFiles/contaGotas.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/contaGotas.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/contaGotas.dir/flags.make

CMakeFiles/contaGotas.dir/MaskGenerator.o: CMakeFiles/contaGotas.dir/flags.make
CMakeFiles/contaGotas.dir/MaskGenerator.o: MaskGenerator.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/rafol/Desktop/PCC/contagotas/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/contaGotas.dir/MaskGenerator.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/contaGotas.dir/MaskGenerator.o -c /home/rafol/Desktop/PCC/contagotas/MaskGenerator.cpp

CMakeFiles/contaGotas.dir/MaskGenerator.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/contaGotas.dir/MaskGenerator.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/rafol/Desktop/PCC/contagotas/MaskGenerator.cpp > CMakeFiles/contaGotas.dir/MaskGenerator.i

CMakeFiles/contaGotas.dir/MaskGenerator.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/contaGotas.dir/MaskGenerator.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/rafol/Desktop/PCC/contagotas/MaskGenerator.cpp -o CMakeFiles/contaGotas.dir/MaskGenerator.s

CMakeFiles/contaGotas.dir/MaskGenerator.o.requires:
.PHONY : CMakeFiles/contaGotas.dir/MaskGenerator.o.requires

CMakeFiles/contaGotas.dir/MaskGenerator.o.provides: CMakeFiles/contaGotas.dir/MaskGenerator.o.requires
	$(MAKE) -f CMakeFiles/contaGotas.dir/build.make CMakeFiles/contaGotas.dir/MaskGenerator.o.provides.build
.PHONY : CMakeFiles/contaGotas.dir/MaskGenerator.o.provides

CMakeFiles/contaGotas.dir/MaskGenerator.o.provides.build: CMakeFiles/contaGotas.dir/MaskGenerator.o
.PHONY : CMakeFiles/contaGotas.dir/MaskGenerator.o.provides.build

CMakeFiles/contaGotas.dir/RGBFilter.o: CMakeFiles/contaGotas.dir/flags.make
CMakeFiles/contaGotas.dir/RGBFilter.o: RGBFilter.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/rafol/Desktop/PCC/contagotas/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/contaGotas.dir/RGBFilter.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/contaGotas.dir/RGBFilter.o -c /home/rafol/Desktop/PCC/contagotas/RGBFilter.cpp

CMakeFiles/contaGotas.dir/RGBFilter.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/contaGotas.dir/RGBFilter.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/rafol/Desktop/PCC/contagotas/RGBFilter.cpp > CMakeFiles/contaGotas.dir/RGBFilter.i

CMakeFiles/contaGotas.dir/RGBFilter.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/contaGotas.dir/RGBFilter.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/rafol/Desktop/PCC/contagotas/RGBFilter.cpp -o CMakeFiles/contaGotas.dir/RGBFilter.s

CMakeFiles/contaGotas.dir/RGBFilter.o.requires:
.PHONY : CMakeFiles/contaGotas.dir/RGBFilter.o.requires

CMakeFiles/contaGotas.dir/RGBFilter.o.provides: CMakeFiles/contaGotas.dir/RGBFilter.o.requires
	$(MAKE) -f CMakeFiles/contaGotas.dir/build.make CMakeFiles/contaGotas.dir/RGBFilter.o.provides.build
.PHONY : CMakeFiles/contaGotas.dir/RGBFilter.o.provides

CMakeFiles/contaGotas.dir/RGBFilter.o.provides.build: CMakeFiles/contaGotas.dir/RGBFilter.o
.PHONY : CMakeFiles/contaGotas.dir/RGBFilter.o.provides.build

CMakeFiles/contaGotas.dir/BlobExtractor.o: CMakeFiles/contaGotas.dir/flags.make
CMakeFiles/contaGotas.dir/BlobExtractor.o: BlobExtractor.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/rafol/Desktop/PCC/contagotas/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/contaGotas.dir/BlobExtractor.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/contaGotas.dir/BlobExtractor.o -c /home/rafol/Desktop/PCC/contagotas/BlobExtractor.cpp

CMakeFiles/contaGotas.dir/BlobExtractor.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/contaGotas.dir/BlobExtractor.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/rafol/Desktop/PCC/contagotas/BlobExtractor.cpp > CMakeFiles/contaGotas.dir/BlobExtractor.i

CMakeFiles/contaGotas.dir/BlobExtractor.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/contaGotas.dir/BlobExtractor.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/rafol/Desktop/PCC/contagotas/BlobExtractor.cpp -o CMakeFiles/contaGotas.dir/BlobExtractor.s

CMakeFiles/contaGotas.dir/BlobExtractor.o.requires:
.PHONY : CMakeFiles/contaGotas.dir/BlobExtractor.o.requires

CMakeFiles/contaGotas.dir/BlobExtractor.o.provides: CMakeFiles/contaGotas.dir/BlobExtractor.o.requires
	$(MAKE) -f CMakeFiles/contaGotas.dir/build.make CMakeFiles/contaGotas.dir/BlobExtractor.o.provides.build
.PHONY : CMakeFiles/contaGotas.dir/BlobExtractor.o.provides

CMakeFiles/contaGotas.dir/BlobExtractor.o.provides.build: CMakeFiles/contaGotas.dir/BlobExtractor.o
.PHONY : CMakeFiles/contaGotas.dir/BlobExtractor.o.provides.build

CMakeFiles/contaGotas.dir/contaGotas.o: CMakeFiles/contaGotas.dir/flags.make
CMakeFiles/contaGotas.dir/contaGotas.o: contaGotas.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/rafol/Desktop/PCC/contagotas/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/contaGotas.dir/contaGotas.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/contaGotas.dir/contaGotas.o -c /home/rafol/Desktop/PCC/contagotas/contaGotas.cpp

CMakeFiles/contaGotas.dir/contaGotas.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/contaGotas.dir/contaGotas.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/rafol/Desktop/PCC/contagotas/contaGotas.cpp > CMakeFiles/contaGotas.dir/contaGotas.i

CMakeFiles/contaGotas.dir/contaGotas.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/contaGotas.dir/contaGotas.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/rafol/Desktop/PCC/contagotas/contaGotas.cpp -o CMakeFiles/contaGotas.dir/contaGotas.s

CMakeFiles/contaGotas.dir/contaGotas.o.requires:
.PHONY : CMakeFiles/contaGotas.dir/contaGotas.o.requires

CMakeFiles/contaGotas.dir/contaGotas.o.provides: CMakeFiles/contaGotas.dir/contaGotas.o.requires
	$(MAKE) -f CMakeFiles/contaGotas.dir/build.make CMakeFiles/contaGotas.dir/contaGotas.o.provides.build
.PHONY : CMakeFiles/contaGotas.dir/contaGotas.o.provides

CMakeFiles/contaGotas.dir/contaGotas.o.provides.build: CMakeFiles/contaGotas.dir/contaGotas.o
.PHONY : CMakeFiles/contaGotas.dir/contaGotas.o.provides.build

# Object files for target contaGotas
contaGotas_OBJECTS = \
"CMakeFiles/contaGotas.dir/MaskGenerator.o" \
"CMakeFiles/contaGotas.dir/RGBFilter.o" \
"CMakeFiles/contaGotas.dir/BlobExtractor.o" \
"CMakeFiles/contaGotas.dir/contaGotas.o"

# External object files for target contaGotas
contaGotas_EXTERNAL_OBJECTS =

contaGotas: CMakeFiles/contaGotas.dir/MaskGenerator.o
contaGotas: CMakeFiles/contaGotas.dir/RGBFilter.o
contaGotas: CMakeFiles/contaGotas.dir/BlobExtractor.o
contaGotas: CMakeFiles/contaGotas.dir/contaGotas.o
contaGotas: /usr/lib/libuuid.so
contaGotas: CMakeFiles/contaGotas.dir/build.make
contaGotas: CMakeFiles/contaGotas.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable contaGotas"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/contaGotas.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/contaGotas.dir/build: contaGotas
.PHONY : CMakeFiles/contaGotas.dir/build

CMakeFiles/contaGotas.dir/requires: CMakeFiles/contaGotas.dir/MaskGenerator.o.requires
CMakeFiles/contaGotas.dir/requires: CMakeFiles/contaGotas.dir/RGBFilter.o.requires
CMakeFiles/contaGotas.dir/requires: CMakeFiles/contaGotas.dir/BlobExtractor.o.requires
CMakeFiles/contaGotas.dir/requires: CMakeFiles/contaGotas.dir/contaGotas.o.requires
.PHONY : CMakeFiles/contaGotas.dir/requires

CMakeFiles/contaGotas.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/contaGotas.dir/cmake_clean.cmake
.PHONY : CMakeFiles/contaGotas.dir/clean

CMakeFiles/contaGotas.dir/depend:
	cd /home/rafol/Desktop/PCC/contagotas && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/rafol/Desktop/PCC/contagotas /home/rafol/Desktop/PCC/contagotas /home/rafol/Desktop/PCC/contagotas /home/rafol/Desktop/PCC/contagotas /home/rafol/Desktop/PCC/contagotas/CMakeFiles/contaGotas.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/contaGotas.dir/depend

