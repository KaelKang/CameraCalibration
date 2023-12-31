# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/rm/Desktop/CaptureNCalibration/calib

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/rm/Desktop/CaptureNCalibration/calib/build

# Include any dependencies generated for this target.
include CMakeFiles/Calib.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Calib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Calib.dir/flags.make

CMakeFiles/Calib.dir/Calibration.cpp.o: CMakeFiles/Calib.dir/flags.make
CMakeFiles/Calib.dir/Calibration.cpp.o: ../Calibration.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rm/Desktop/CaptureNCalibration/calib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Calib.dir/Calibration.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Calib.dir/Calibration.cpp.o -c /home/rm/Desktop/CaptureNCalibration/calib/Calibration.cpp

CMakeFiles/Calib.dir/Calibration.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Calib.dir/Calibration.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/rm/Desktop/CaptureNCalibration/calib/Calibration.cpp > CMakeFiles/Calib.dir/Calibration.cpp.i

CMakeFiles/Calib.dir/Calibration.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Calib.dir/Calibration.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/rm/Desktop/CaptureNCalibration/calib/Calibration.cpp -o CMakeFiles/Calib.dir/Calibration.cpp.s

CMakeFiles/Calib.dir/home/rm/Desktop/CaptureNCalibration/Camera/src/GxCamera.cpp.o: CMakeFiles/Calib.dir/flags.make
CMakeFiles/Calib.dir/home/rm/Desktop/CaptureNCalibration/Camera/src/GxCamera.cpp.o: /home/rm/Desktop/CaptureNCalibration/Camera/src/GxCamera.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rm/Desktop/CaptureNCalibration/calib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Calib.dir/home/rm/Desktop/CaptureNCalibration/Camera/src/GxCamera.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Calib.dir/home/rm/Desktop/CaptureNCalibration/Camera/src/GxCamera.cpp.o -c /home/rm/Desktop/CaptureNCalibration/Camera/src/GxCamera.cpp

CMakeFiles/Calib.dir/home/rm/Desktop/CaptureNCalibration/Camera/src/GxCamera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Calib.dir/home/rm/Desktop/CaptureNCalibration/Camera/src/GxCamera.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/rm/Desktop/CaptureNCalibration/Camera/src/GxCamera.cpp > CMakeFiles/Calib.dir/home/rm/Desktop/CaptureNCalibration/Camera/src/GxCamera.cpp.i

CMakeFiles/Calib.dir/home/rm/Desktop/CaptureNCalibration/Camera/src/GxCamera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Calib.dir/home/rm/Desktop/CaptureNCalibration/Camera/src/GxCamera.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/rm/Desktop/CaptureNCalibration/Camera/src/GxCamera.cpp -o CMakeFiles/Calib.dir/home/rm/Desktop/CaptureNCalibration/Camera/src/GxCamera.cpp.s

# Object files for target Calib
Calib_OBJECTS = \
"CMakeFiles/Calib.dir/Calibration.cpp.o" \
"CMakeFiles/Calib.dir/home/rm/Desktop/CaptureNCalibration/Camera/src/GxCamera.cpp.o"

# External object files for target Calib
Calib_EXTERNAL_OBJECTS =

Calib: CMakeFiles/Calib.dir/Calibration.cpp.o
Calib: CMakeFiles/Calib.dir/home/rm/Desktop/CaptureNCalibration/Camera/src/GxCamera.cpp.o
Calib: CMakeFiles/Calib.dir/build.make
Calib: /opt/intel/openvino_2021/opencv/lib/libopencv_gapi.so.4.5.3
Calib: /opt/intel/openvino_2021/opencv/lib/libopencv_highgui.so.4.5.3
Calib: /opt/intel/openvino_2021/opencv/lib/libopencv_ml.so.4.5.3
Calib: /opt/intel/openvino_2021/opencv/lib/libopencv_objdetect.so.4.5.3
Calib: /opt/intel/openvino_2021/opencv/lib/libopencv_photo.so.4.5.3
Calib: /opt/intel/openvino_2021/opencv/lib/libopencv_stitching.so.4.5.3
Calib: /opt/intel/openvino_2021/opencv/lib/libopencv_video.so.4.5.3
Calib: /opt/intel/openvino_2021/opencv/lib/libopencv_videoio.so.4.5.3
Calib: /opt/intel/openvino_2021/opencv/lib/libopencv_dnn.so.4.5.3
Calib: /opt/intel/openvino_2021/deployment_tools/inference_engine/lib/intel64/libinference_engine.so
Calib: /opt/intel/openvino_2021/deployment_tools/inference_engine/lib/intel64/libinference_engine_c_api.so
Calib: /opt/intel/openvino_2021/opencv/lib/libopencv_imgcodecs.so.4.5.3
Calib: /opt/intel/openvino_2021/opencv/lib/libopencv_calib3d.so.4.5.3
Calib: /opt/intel/openvino_2021/opencv/lib/libopencv_features2d.so.4.5.3
Calib: /opt/intel/openvino_2021/opencv/lib/libopencv_flann.so.4.5.3
Calib: /opt/intel/openvino_2021/opencv/lib/libopencv_imgproc.so.4.5.3
Calib: /opt/intel/openvino_2021/opencv/lib/libopencv_core.so.4.5.3
Calib: CMakeFiles/Calib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/rm/Desktop/CaptureNCalibration/calib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable Calib"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Calib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Calib.dir/build: Calib

.PHONY : CMakeFiles/Calib.dir/build

CMakeFiles/Calib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Calib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Calib.dir/clean

CMakeFiles/Calib.dir/depend:
	cd /home/rm/Desktop/CaptureNCalibration/calib/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/rm/Desktop/CaptureNCalibration/calib /home/rm/Desktop/CaptureNCalibration/calib /home/rm/Desktop/CaptureNCalibration/calib/build /home/rm/Desktop/CaptureNCalibration/calib/build /home/rm/Desktop/CaptureNCalibration/calib/build/CMakeFiles/Calib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Calib.dir/depend

