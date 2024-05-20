# Install script for directory: /home/szj/myTask/test_link_UR/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/szj/myTask/test_link_UR/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  
      if (NOT EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}")
        file(MAKE_DIRECTORY "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}")
      endif()
      if (NOT EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/.catkin")
        file(WRITE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/.catkin" "")
      endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/szj/myTask/test_link_UR/install/_setup_util.py")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/szj/myTask/test_link_UR/install" TYPE PROGRAM FILES "/home/szj/myTask/test_link_UR/build/catkin_generated/installspace/_setup_util.py")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/szj/myTask/test_link_UR/install/env.sh")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/szj/myTask/test_link_UR/install" TYPE PROGRAM FILES "/home/szj/myTask/test_link_UR/build/catkin_generated/installspace/env.sh")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/szj/myTask/test_link_UR/install/setup.bash;/home/szj/myTask/test_link_UR/install/local_setup.bash")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/szj/myTask/test_link_UR/install" TYPE FILE FILES
    "/home/szj/myTask/test_link_UR/build/catkin_generated/installspace/setup.bash"
    "/home/szj/myTask/test_link_UR/build/catkin_generated/installspace/local_setup.bash"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/szj/myTask/test_link_UR/install/setup.sh;/home/szj/myTask/test_link_UR/install/local_setup.sh")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/szj/myTask/test_link_UR/install" TYPE FILE FILES
    "/home/szj/myTask/test_link_UR/build/catkin_generated/installspace/setup.sh"
    "/home/szj/myTask/test_link_UR/build/catkin_generated/installspace/local_setup.sh"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/szj/myTask/test_link_UR/install/setup.zsh;/home/szj/myTask/test_link_UR/install/local_setup.zsh")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/szj/myTask/test_link_UR/install" TYPE FILE FILES
    "/home/szj/myTask/test_link_UR/build/catkin_generated/installspace/setup.zsh"
    "/home/szj/myTask/test_link_UR/build/catkin_generated/installspace/local_setup.zsh"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/szj/myTask/test_link_UR/install/.rosinstall")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/szj/myTask/test_link_UR/install" TYPE FILE FILES "/home/szj/myTask/test_link_UR/build/catkin_generated/installspace/.rosinstall")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/szj/myTask/test_link_UR/build/gtest/cmake_install.cmake")
  include("/home/szj/myTask/test_link_UR/build/msg/cartesian_state_msgs/cmake_install.cmake")
  include("/home/szj/myTask/test_link_UR/build/UR_robot/fmauch_universal_robot/universal_robots/cmake_install.cmake")
  include("/home/szj/myTask/test_link_UR/build/UR_robot/Universal_Robots_ROS_Driver/ur_dashboard_msgs/cmake_install.cmake")
  include("/home/szj/myTask/test_link_UR/build/UR_robot/ur_msgs/cmake_install.cmake")
  include("/home/szj/myTask/test_link_UR/build/msg/joint_state_msg/cmake_install.cmake")
  include("/home/szj/myTask/test_link_UR/build/force_sensor/etherdaq_ros/cmake_install.cmake")
  include("/home/szj/myTask/test_link_UR/build/controller/szj_controller/cmake_install.cmake")
  include("/home/szj/myTask/test_link_UR/build/test_demo/cmake_install.cmake")
  include("/home/szj/myTask/test_link_UR/build/controller/force_control/cmake_install.cmake")
  include("/home/szj/myTask/test_link_UR/build/from_zero_force_trajectory/cmake_install.cmake")
  include("/home/szj/myTask/test_link_UR/build/UR_robot/fmauch_universal_robot/ur_description/cmake_install.cmake")
  include("/home/szj/myTask/test_link_UR/build/UR_robot/fmauch_universal_robot/ur_gazebo/cmake_install.cmake")
  include("/home/szj/myTask/test_link_UR/build/controller/cartesian_velocity_position_controller/cmake_install.cmake")
  include("/home/szj/myTask/test_link_UR/build/UR_robot/fmauch_universal_robot/ur_kinematics/cmake_install.cmake")
  include("/home/szj/myTask/test_link_UR/build/controller/admittance_controller/cmake_install.cmake")
  include("/home/szj/myTask/test_link_UR/build/force_sensor/gravity_compensate/cmake_install.cmake")
  include("/home/szj/myTask/test_link_UR/build/szj_demo/cmake_install.cmake")
  include("/home/szj/myTask/test_link_UR/build/force_sensor/wrench_filter/cmake_install.cmake")
  include("/home/szj/myTask/test_link_UR/build/UR_robot/fmauch_universal_robot/ur10_moveit_config/cmake_install.cmake")
  include("/home/szj/myTask/test_link_UR/build/UR_robot/fmauch_universal_robot/ur10e_moveit_config/cmake_install.cmake")
  include("/home/szj/myTask/test_link_UR/build/UR_robot/fmauch_universal_robot/ur16e_moveit_config/cmake_install.cmake")
  include("/home/szj/myTask/test_link_UR/build/UR_robot/fmauch_universal_robot/ur3_moveit_config/cmake_install.cmake")
  include("/home/szj/myTask/test_link_UR/build/UR_robot/fmauch_universal_robot/ur3e_moveit_config/cmake_install.cmake")
  include("/home/szj/myTask/test_link_UR/build/UR_robot/fmauch_universal_robot/ur5_moveit_config/cmake_install.cmake")
  include("/home/szj/myTask/test_link_UR/build/UR_robot/fmauch_universal_robot/ur5e_moveit_config/cmake_install.cmake")
  include("/home/szj/myTask/test_link_UR/build/UR_robot/Universal_Robots_ROS_Driver/ur_robot_driver/cmake_install.cmake")
  include("/home/szj/myTask/test_link_UR/build/controller/test_controller/cmake_install.cmake")
  include("/home/szj/myTask/test_link_UR/build/UR_robot/Universal_Robots_ROS_Driver/ur_calibration/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/szj/myTask/test_link_UR/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
