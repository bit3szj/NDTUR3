# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "admittance_controller: 2 messages, 1 services")

set(MSG_I_FLAGS "-Iadmittance_controller:/home/szj/myTask/test_link_UR/src/admittance_controller/msg;-Istd_msgs:/opt/ros/noetic/share/std_msgs/cmake/../msg;-Isensor_msgs:/opt/ros/noetic/share/sensor_msgs/cmake/../msg;-Iadmittance_controller:/home/szj/myTask/test_link_UR/src/admittance_controller/msg;-Igeometry_msgs:/opt/ros/noetic/share/geometry_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(admittance_controller_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/szj/myTask/test_link_UR/src/admittance_controller/msg/joint_trajectory.msg" NAME_WE)
add_custom_target(_admittance_controller_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "admittance_controller" "/home/szj/myTask/test_link_UR/src/admittance_controller/msg/joint_trajectory.msg" "sensor_msgs/JointState:std_msgs/Header:admittance_controller/parameter_msg"
)

get_filename_component(_filename "/home/szj/myTask/test_link_UR/src/admittance_controller/msg/parameter_msg.msg" NAME_WE)
add_custom_target(_admittance_controller_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "admittance_controller" "/home/szj/myTask/test_link_UR/src/admittance_controller/msg/parameter_msg.msg" ""
)

get_filename_component(_filename "/home/szj/myTask/test_link_UR/src/admittance_controller/srv/parameter_srv.srv" NAME_WE)
add_custom_target(_admittance_controller_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "admittance_controller" "/home/szj/myTask/test_link_UR/src/admittance_controller/srv/parameter_srv.srv" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(admittance_controller
  "/home/szj/myTask/test_link_UR/src/admittance_controller/msg/joint_trajectory.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/sensor_msgs/cmake/../msg/JointState.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/home/szj/myTask/test_link_UR/src/admittance_controller/msg/parameter_msg.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/admittance_controller
)
_generate_msg_cpp(admittance_controller
  "/home/szj/myTask/test_link_UR/src/admittance_controller/msg/parameter_msg.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/admittance_controller
)

### Generating Services
_generate_srv_cpp(admittance_controller
  "/home/szj/myTask/test_link_UR/src/admittance_controller/srv/parameter_srv.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/admittance_controller
)

### Generating Module File
_generate_module_cpp(admittance_controller
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/admittance_controller
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(admittance_controller_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(admittance_controller_generate_messages admittance_controller_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/szj/myTask/test_link_UR/src/admittance_controller/msg/joint_trajectory.msg" NAME_WE)
add_dependencies(admittance_controller_generate_messages_cpp _admittance_controller_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/szj/myTask/test_link_UR/src/admittance_controller/msg/parameter_msg.msg" NAME_WE)
add_dependencies(admittance_controller_generate_messages_cpp _admittance_controller_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/szj/myTask/test_link_UR/src/admittance_controller/srv/parameter_srv.srv" NAME_WE)
add_dependencies(admittance_controller_generate_messages_cpp _admittance_controller_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(admittance_controller_gencpp)
add_dependencies(admittance_controller_gencpp admittance_controller_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS admittance_controller_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(admittance_controller
  "/home/szj/myTask/test_link_UR/src/admittance_controller/msg/joint_trajectory.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/sensor_msgs/cmake/../msg/JointState.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/home/szj/myTask/test_link_UR/src/admittance_controller/msg/parameter_msg.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/admittance_controller
)
_generate_msg_eus(admittance_controller
  "/home/szj/myTask/test_link_UR/src/admittance_controller/msg/parameter_msg.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/admittance_controller
)

### Generating Services
_generate_srv_eus(admittance_controller
  "/home/szj/myTask/test_link_UR/src/admittance_controller/srv/parameter_srv.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/admittance_controller
)

### Generating Module File
_generate_module_eus(admittance_controller
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/admittance_controller
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(admittance_controller_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(admittance_controller_generate_messages admittance_controller_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/szj/myTask/test_link_UR/src/admittance_controller/msg/joint_trajectory.msg" NAME_WE)
add_dependencies(admittance_controller_generate_messages_eus _admittance_controller_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/szj/myTask/test_link_UR/src/admittance_controller/msg/parameter_msg.msg" NAME_WE)
add_dependencies(admittance_controller_generate_messages_eus _admittance_controller_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/szj/myTask/test_link_UR/src/admittance_controller/srv/parameter_srv.srv" NAME_WE)
add_dependencies(admittance_controller_generate_messages_eus _admittance_controller_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(admittance_controller_geneus)
add_dependencies(admittance_controller_geneus admittance_controller_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS admittance_controller_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(admittance_controller
  "/home/szj/myTask/test_link_UR/src/admittance_controller/msg/joint_trajectory.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/sensor_msgs/cmake/../msg/JointState.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/home/szj/myTask/test_link_UR/src/admittance_controller/msg/parameter_msg.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/admittance_controller
)
_generate_msg_lisp(admittance_controller
  "/home/szj/myTask/test_link_UR/src/admittance_controller/msg/parameter_msg.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/admittance_controller
)

### Generating Services
_generate_srv_lisp(admittance_controller
  "/home/szj/myTask/test_link_UR/src/admittance_controller/srv/parameter_srv.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/admittance_controller
)

### Generating Module File
_generate_module_lisp(admittance_controller
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/admittance_controller
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(admittance_controller_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(admittance_controller_generate_messages admittance_controller_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/szj/myTask/test_link_UR/src/admittance_controller/msg/joint_trajectory.msg" NAME_WE)
add_dependencies(admittance_controller_generate_messages_lisp _admittance_controller_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/szj/myTask/test_link_UR/src/admittance_controller/msg/parameter_msg.msg" NAME_WE)
add_dependencies(admittance_controller_generate_messages_lisp _admittance_controller_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/szj/myTask/test_link_UR/src/admittance_controller/srv/parameter_srv.srv" NAME_WE)
add_dependencies(admittance_controller_generate_messages_lisp _admittance_controller_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(admittance_controller_genlisp)
add_dependencies(admittance_controller_genlisp admittance_controller_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS admittance_controller_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(admittance_controller
  "/home/szj/myTask/test_link_UR/src/admittance_controller/msg/joint_trajectory.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/sensor_msgs/cmake/../msg/JointState.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/home/szj/myTask/test_link_UR/src/admittance_controller/msg/parameter_msg.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/admittance_controller
)
_generate_msg_nodejs(admittance_controller
  "/home/szj/myTask/test_link_UR/src/admittance_controller/msg/parameter_msg.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/admittance_controller
)

### Generating Services
_generate_srv_nodejs(admittance_controller
  "/home/szj/myTask/test_link_UR/src/admittance_controller/srv/parameter_srv.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/admittance_controller
)

### Generating Module File
_generate_module_nodejs(admittance_controller
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/admittance_controller
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(admittance_controller_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(admittance_controller_generate_messages admittance_controller_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/szj/myTask/test_link_UR/src/admittance_controller/msg/joint_trajectory.msg" NAME_WE)
add_dependencies(admittance_controller_generate_messages_nodejs _admittance_controller_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/szj/myTask/test_link_UR/src/admittance_controller/msg/parameter_msg.msg" NAME_WE)
add_dependencies(admittance_controller_generate_messages_nodejs _admittance_controller_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/szj/myTask/test_link_UR/src/admittance_controller/srv/parameter_srv.srv" NAME_WE)
add_dependencies(admittance_controller_generate_messages_nodejs _admittance_controller_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(admittance_controller_gennodejs)
add_dependencies(admittance_controller_gennodejs admittance_controller_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS admittance_controller_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(admittance_controller
  "/home/szj/myTask/test_link_UR/src/admittance_controller/msg/joint_trajectory.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/noetic/share/sensor_msgs/cmake/../msg/JointState.msg;/opt/ros/noetic/share/std_msgs/cmake/../msg/Header.msg;/home/szj/myTask/test_link_UR/src/admittance_controller/msg/parameter_msg.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/admittance_controller
)
_generate_msg_py(admittance_controller
  "/home/szj/myTask/test_link_UR/src/admittance_controller/msg/parameter_msg.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/admittance_controller
)

### Generating Services
_generate_srv_py(admittance_controller
  "/home/szj/myTask/test_link_UR/src/admittance_controller/srv/parameter_srv.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/admittance_controller
)

### Generating Module File
_generate_module_py(admittance_controller
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/admittance_controller
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(admittance_controller_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(admittance_controller_generate_messages admittance_controller_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/szj/myTask/test_link_UR/src/admittance_controller/msg/joint_trajectory.msg" NAME_WE)
add_dependencies(admittance_controller_generate_messages_py _admittance_controller_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/szj/myTask/test_link_UR/src/admittance_controller/msg/parameter_msg.msg" NAME_WE)
add_dependencies(admittance_controller_generate_messages_py _admittance_controller_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/szj/myTask/test_link_UR/src/admittance_controller/srv/parameter_srv.srv" NAME_WE)
add_dependencies(admittance_controller_generate_messages_py _admittance_controller_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(admittance_controller_genpy)
add_dependencies(admittance_controller_genpy admittance_controller_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS admittance_controller_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/admittance_controller)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/admittance_controller
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(admittance_controller_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()
if(TARGET sensor_msgs_generate_messages_cpp)
  add_dependencies(admittance_controller_generate_messages_cpp sensor_msgs_generate_messages_cpp)
endif()
if(TARGET admittance_controller_generate_messages_cpp)
  add_dependencies(admittance_controller_generate_messages_cpp admittance_controller_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/admittance_controller)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/admittance_controller
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(admittance_controller_generate_messages_eus std_msgs_generate_messages_eus)
endif()
if(TARGET sensor_msgs_generate_messages_eus)
  add_dependencies(admittance_controller_generate_messages_eus sensor_msgs_generate_messages_eus)
endif()
if(TARGET admittance_controller_generate_messages_eus)
  add_dependencies(admittance_controller_generate_messages_eus admittance_controller_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/admittance_controller)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/admittance_controller
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(admittance_controller_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()
if(TARGET sensor_msgs_generate_messages_lisp)
  add_dependencies(admittance_controller_generate_messages_lisp sensor_msgs_generate_messages_lisp)
endif()
if(TARGET admittance_controller_generate_messages_lisp)
  add_dependencies(admittance_controller_generate_messages_lisp admittance_controller_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/admittance_controller)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/admittance_controller
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(admittance_controller_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()
if(TARGET sensor_msgs_generate_messages_nodejs)
  add_dependencies(admittance_controller_generate_messages_nodejs sensor_msgs_generate_messages_nodejs)
endif()
if(TARGET admittance_controller_generate_messages_nodejs)
  add_dependencies(admittance_controller_generate_messages_nodejs admittance_controller_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/admittance_controller)
  install(CODE "execute_process(COMMAND \"/usr/bin/python3\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/admittance_controller\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/admittance_controller
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(admittance_controller_generate_messages_py std_msgs_generate_messages_py)
endif()
if(TARGET sensor_msgs_generate_messages_py)
  add_dependencies(admittance_controller_generate_messages_py sensor_msgs_generate_messages_py)
endif()
if(TARGET admittance_controller_generate_messages_py)
  add_dependencies(admittance_controller_generate_messages_py admittance_controller_generate_messages_py)
endif()
