# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "szj_demo: 2 messages, 0 services")

set(MSG_I_FLAGS "-Iszj_demo:/home/szj/myTask/test_link_UR/src/szj_demo/msg;-Istd_msgs:/opt/ros/noetic/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(szj_demo_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/szj/myTask/test_link_UR/src/szj_demo/msg/toolStatus.msg" NAME_WE)
add_custom_target(_szj_demo_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "szj_demo" "/home/szj/myTask/test_link_UR/src/szj_demo/msg/toolStatus.msg" ""
)

get_filename_component(_filename "/home/szj/myTask/test_link_UR/src/szj_demo/msg/AdmStatus.msg" NAME_WE)
add_custom_target(_szj_demo_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "szj_demo" "/home/szj/myTask/test_link_UR/src/szj_demo/msg/AdmStatus.msg" ""
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(szj_demo
  "/home/szj/myTask/test_link_UR/src/szj_demo/msg/toolStatus.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/szj_demo
)
_generate_msg_cpp(szj_demo
  "/home/szj/myTask/test_link_UR/src/szj_demo/msg/AdmStatus.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/szj_demo
)

### Generating Services

### Generating Module File
_generate_module_cpp(szj_demo
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/szj_demo
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(szj_demo_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(szj_demo_generate_messages szj_demo_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/szj/myTask/test_link_UR/src/szj_demo/msg/toolStatus.msg" NAME_WE)
add_dependencies(szj_demo_generate_messages_cpp _szj_demo_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/szj/myTask/test_link_UR/src/szj_demo/msg/AdmStatus.msg" NAME_WE)
add_dependencies(szj_demo_generate_messages_cpp _szj_demo_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(szj_demo_gencpp)
add_dependencies(szj_demo_gencpp szj_demo_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS szj_demo_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(szj_demo
  "/home/szj/myTask/test_link_UR/src/szj_demo/msg/toolStatus.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/szj_demo
)
_generate_msg_eus(szj_demo
  "/home/szj/myTask/test_link_UR/src/szj_demo/msg/AdmStatus.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/szj_demo
)

### Generating Services

### Generating Module File
_generate_module_eus(szj_demo
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/szj_demo
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(szj_demo_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(szj_demo_generate_messages szj_demo_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/szj/myTask/test_link_UR/src/szj_demo/msg/toolStatus.msg" NAME_WE)
add_dependencies(szj_demo_generate_messages_eus _szj_demo_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/szj/myTask/test_link_UR/src/szj_demo/msg/AdmStatus.msg" NAME_WE)
add_dependencies(szj_demo_generate_messages_eus _szj_demo_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(szj_demo_geneus)
add_dependencies(szj_demo_geneus szj_demo_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS szj_demo_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(szj_demo
  "/home/szj/myTask/test_link_UR/src/szj_demo/msg/toolStatus.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/szj_demo
)
_generate_msg_lisp(szj_demo
  "/home/szj/myTask/test_link_UR/src/szj_demo/msg/AdmStatus.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/szj_demo
)

### Generating Services

### Generating Module File
_generate_module_lisp(szj_demo
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/szj_demo
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(szj_demo_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(szj_demo_generate_messages szj_demo_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/szj/myTask/test_link_UR/src/szj_demo/msg/toolStatus.msg" NAME_WE)
add_dependencies(szj_demo_generate_messages_lisp _szj_demo_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/szj/myTask/test_link_UR/src/szj_demo/msg/AdmStatus.msg" NAME_WE)
add_dependencies(szj_demo_generate_messages_lisp _szj_demo_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(szj_demo_genlisp)
add_dependencies(szj_demo_genlisp szj_demo_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS szj_demo_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(szj_demo
  "/home/szj/myTask/test_link_UR/src/szj_demo/msg/toolStatus.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/szj_demo
)
_generate_msg_nodejs(szj_demo
  "/home/szj/myTask/test_link_UR/src/szj_demo/msg/AdmStatus.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/szj_demo
)

### Generating Services

### Generating Module File
_generate_module_nodejs(szj_demo
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/szj_demo
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(szj_demo_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(szj_demo_generate_messages szj_demo_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/szj/myTask/test_link_UR/src/szj_demo/msg/toolStatus.msg" NAME_WE)
add_dependencies(szj_demo_generate_messages_nodejs _szj_demo_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/szj/myTask/test_link_UR/src/szj_demo/msg/AdmStatus.msg" NAME_WE)
add_dependencies(szj_demo_generate_messages_nodejs _szj_demo_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(szj_demo_gennodejs)
add_dependencies(szj_demo_gennodejs szj_demo_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS szj_demo_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(szj_demo
  "/home/szj/myTask/test_link_UR/src/szj_demo/msg/toolStatus.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/szj_demo
)
_generate_msg_py(szj_demo
  "/home/szj/myTask/test_link_UR/src/szj_demo/msg/AdmStatus.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/szj_demo
)

### Generating Services

### Generating Module File
_generate_module_py(szj_demo
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/szj_demo
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(szj_demo_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(szj_demo_generate_messages szj_demo_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/szj/myTask/test_link_UR/src/szj_demo/msg/toolStatus.msg" NAME_WE)
add_dependencies(szj_demo_generate_messages_py _szj_demo_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/szj/myTask/test_link_UR/src/szj_demo/msg/AdmStatus.msg" NAME_WE)
add_dependencies(szj_demo_generate_messages_py _szj_demo_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(szj_demo_genpy)
add_dependencies(szj_demo_genpy szj_demo_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS szj_demo_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/szj_demo)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/szj_demo
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(szj_demo_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/szj_demo)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/szj_demo
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(szj_demo_generate_messages_eus std_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/szj_demo)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/szj_demo
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(szj_demo_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/szj_demo)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/szj_demo
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(szj_demo_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/szj_demo)
  install(CODE "execute_process(COMMAND \"/usr/bin/python3\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/szj_demo\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/szj_demo
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(szj_demo_generate_messages_py std_msgs_generate_messages_py)
endif()
