; Auto-generated. Do not edit!


(cl:in-package admittance_controller-msg)


;//! \htmlinclude joint_trajectory.msg.html

(cl:defclass <joint_trajectory> (roslisp-msg-protocol:ros-message)
  ((trajectory
    :reader trajectory
    :initarg :trajectory
    :type (cl:vector sensor_msgs-msg:JointState)
   :initform (cl:make-array 0 :element-type 'sensor_msgs-msg:JointState :initial-element (cl:make-instance 'sensor_msgs-msg:JointState)))
   (extra_data
    :reader extra_data
    :initarg :extra_data
    :type (cl:vector admittance_controller-msg:parameter_msg)
   :initform (cl:make-array 0 :element-type 'admittance_controller-msg:parameter_msg :initial-element (cl:make-instance 'admittance_controller-msg:parameter_msg)))
   (velocity_scaling_percentage
    :reader velocity_scaling_percentage
    :initarg :velocity_scaling_percentage
    :type cl:integer
    :initform 0))
)

(cl:defclass joint_trajectory (<joint_trajectory>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <joint_trajectory>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'joint_trajectory)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name admittance_controller-msg:<joint_trajectory> is deprecated: use admittance_controller-msg:joint_trajectory instead.")))

(cl:ensure-generic-function 'trajectory-val :lambda-list '(m))
(cl:defmethod trajectory-val ((m <joint_trajectory>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader admittance_controller-msg:trajectory-val is deprecated.  Use admittance_controller-msg:trajectory instead.")
  (trajectory m))

(cl:ensure-generic-function 'extra_data-val :lambda-list '(m))
(cl:defmethod extra_data-val ((m <joint_trajectory>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader admittance_controller-msg:extra_data-val is deprecated.  Use admittance_controller-msg:extra_data instead.")
  (extra_data m))

(cl:ensure-generic-function 'velocity_scaling_percentage-val :lambda-list '(m))
(cl:defmethod velocity_scaling_percentage-val ((m <joint_trajectory>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader admittance_controller-msg:velocity_scaling_percentage-val is deprecated.  Use admittance_controller-msg:velocity_scaling_percentage instead.")
  (velocity_scaling_percentage m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <joint_trajectory>) ostream)
  "Serializes a message object of type '<joint_trajectory>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'trajectory))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'trajectory))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'extra_data))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'extra_data))
  (cl:let* ((signed (cl:slot-value msg 'velocity_scaling_percentage)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 18446744073709551616) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <joint_trajectory>) istream)
  "Deserializes a message object of type '<joint_trajectory>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'trajectory) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'trajectory)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'sensor_msgs-msg:JointState))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'extra_data) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'extra_data)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'admittance_controller-msg:parameter_msg))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'velocity_scaling_percentage) (cl:if (cl:< unsigned 9223372036854775808) unsigned (cl:- unsigned 18446744073709551616))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<joint_trajectory>)))
  "Returns string type for a message object of type '<joint_trajectory>"
  "admittance_controller/joint_trajectory")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'joint_trajectory)))
  "Returns string type for a message object of type 'joint_trajectory"
  "admittance_controller/joint_trajectory")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<joint_trajectory>)))
  "Returns md5sum for a message object of type '<joint_trajectory>"
  "9047f34bd5bbdb3efed33b5595650679")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'joint_trajectory)))
  "Returns md5sum for a message object of type 'joint_trajectory"
  "9047f34bd5bbdb3efed33b5595650679")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<joint_trajectory>)))
  "Returns full string definition for message of type '<joint_trajectory>"
  (cl:format cl:nil "sensor_msgs/JointState[] trajectory~%parameter_msg[] extra_data~%int64 velocity_scaling_percentage~%~%================================================================================~%MSG: sensor_msgs/JointState~%# This is a message that holds data to describe the state of a set of torque controlled joints. ~%#~%# The state of each joint (revolute or prismatic) is defined by:~%#  * the position of the joint (rad or m),~%#  * the velocity of the joint (rad/s or m/s) and ~%#  * the effort that is applied in the joint (Nm or N).~%#~%# Each joint is uniquely identified by its name~%# The header specifies the time at which the joint states were recorded. All the joint states~%# in one message have to be recorded at the same time.~%#~%# This message consists of a multiple arrays, one for each part of the joint state. ~%# The goal is to make each of the fields optional. When e.g. your joints have no~%# effort associated with them, you can leave the effort array empty. ~%#~%# All arrays in this message should have the same size, or be empty.~%# This is the only way to uniquely associate the joint name with the correct~%# states.~%~%~%Header header~%~%string[] name~%float64[] position~%float64[] velocity~%float64[] effort~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: admittance_controller/parameter_msg~%string parameter_name~%float32 parameter_value~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'joint_trajectory)))
  "Returns full string definition for message of type 'joint_trajectory"
  (cl:format cl:nil "sensor_msgs/JointState[] trajectory~%parameter_msg[] extra_data~%int64 velocity_scaling_percentage~%~%================================================================================~%MSG: sensor_msgs/JointState~%# This is a message that holds data to describe the state of a set of torque controlled joints. ~%#~%# The state of each joint (revolute or prismatic) is defined by:~%#  * the position of the joint (rad or m),~%#  * the velocity of the joint (rad/s or m/s) and ~%#  * the effort that is applied in the joint (Nm or N).~%#~%# Each joint is uniquely identified by its name~%# The header specifies the time at which the joint states were recorded. All the joint states~%# in one message have to be recorded at the same time.~%#~%# This message consists of a multiple arrays, one for each part of the joint state. ~%# The goal is to make each of the fields optional. When e.g. your joints have no~%# effort associated with them, you can leave the effort array empty. ~%#~%# All arrays in this message should have the same size, or be empty.~%# This is the only way to uniquely associate the joint name with the correct~%# states.~%~%~%Header header~%~%string[] name~%float64[] position~%float64[] velocity~%float64[] effort~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: admittance_controller/parameter_msg~%string parameter_name~%float32 parameter_value~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <joint_trajectory>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'trajectory) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'extra_data) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <joint_trajectory>))
  "Converts a ROS message object to a list"
  (cl:list 'joint_trajectory
    (cl:cons ':trajectory (trajectory msg))
    (cl:cons ':extra_data (extra_data msg))
    (cl:cons ':velocity_scaling_percentage (velocity_scaling_percentage msg))
))
