cmake_minimum_required(VERSION 2.8.3)
project(d_d)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS "-std=c++11 -DEIGEN_DONT_PARALLELIZE ")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -g")
set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")


find_package(catkin REQUIRED COMPONENTS
  dynamic_reconfigure
  roscpp
  rospy
  cv_bridge
  image_transport
)

find_package(OpenCV REQUIRED)

generate_dynamic_reconfigure_options(
  cfg/Change.cfg
)

include_directories(
  src
  ${catkin_INCLUDE_DIRS}
)

# for dynamic reconfigure  
add_executable(dynamic_reconfigure_node
	src/server.cpp
	src/detector.cpp
	) 

# make sure configure headers are built before any node using them
add_dependencies(dynamic_reconfigure_node ${PROJECT_NAME}_gencfg)

# for dynamic reconfigure  
target_link_libraries(dynamic_reconfigure_node ${catkin_LIBRARIES} ${OpenCV_LIBS} "libjsoncpp.a" )  

catkin_package(
)

