cmake_minimum_required(VERSION 3.15)
project(Calib)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++17 -Os -pthread -g")

find_package(OpenCV 4.5.0)
# set(CMAKE_PREFIX_PATH /opt/intel/openvino_2021/deployment_tools/inference_engine/share)
# find_package(InferenceEngine REQUIRED)
find_package(Eigen3 REQUIRED)


include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${EIGEN3_INCLUDE_DIRS})
# include_directories(${InferenceEngine_INCLUDE_DIRS})


include_directories(
# include
  /usr/local/include
  /usr/lib
  ${EIGEN3_INCLUDE_DIRS}
  ../Camera/include
)

AUX_SOURCE_DIRECTORY(../Camera/src DIR_SRCS)
SET( src_list
  ${DIR_SRCS}
)


add_executable(Calib Calibration.cpp 

    ${src_list} )
target_link_libraries(Calib
    ${OpenCV_LIBRARIES} 
#     ${InferenceEngine_LIBRARIES} 
    ${Eigen3_LIBRARIES}    
    ${CMAKE_THREAD_LIBS_INIT}
#    gxiapi 
)