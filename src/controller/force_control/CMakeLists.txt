cmake_minimum_required(VERSION 3.0.2)
project(force_control)



find_package(catkin REQUIRED COMPONENTS
  roscpp
  geometry_msgs
  std_msgs
  sensor_msgs
)
find_package(Eigen3 REQUIRED)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES force_control
#  CATKIN_DEPENDS roscpp
#  DEPENDS system_lib
)


include_directories(
# include
  ${EIGEN3_INCLUDE_DIRS}
  ${catkin_INCLUDE_DIRS}
)


add_executable(admittance_control_node src/admittance_control.cpp)
target_link_libraries(admittance_control_node
  ${catkin_LIBRARIES}
  ${EIGEN3_LIBRARIES}
)





add_executable(publish_tool_velocity_node src/publish_tool_velocity.cpp)
target_link_libraries(publish_tool_velocity_node
  ${catkin_LIBRARIES}
  ${EIGEN3_LIBRARIES}
)

add_executable(control_move_node src/control_move.cpp)
target_link_libraries(control_move_node
  ${catkin_LIBRARIES}
)
