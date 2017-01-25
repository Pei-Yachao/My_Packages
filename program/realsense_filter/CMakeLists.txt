cmake_minimum_required(VERSION 2.8.3)
project(realsense_filter)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(PCL 1.6 REQUIRED)

find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  cv_bridge
  pcl_conversions
  pcl_msgs
  roscpp
  sensor_msgs
  std_msgs
  tf
  pcl_ros
  
)


catkin_package(

)


include_directories(
  ${catkin_INCLUDE_DIRS}
  ${PCL_INCLUDE_DIRS}
)

link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})


add_executable(voxel_filter src/realsense_cloud_voxel_filtering.cpp)
target_link_libraries(voxel_filter ${catkin_LIBRARIES})

add_executable(multi_xtion_tf src/multi_xtion_tf.cpp)
target_link_libraries(multi_xtion_tf ${catkin_LIBRARIES})
