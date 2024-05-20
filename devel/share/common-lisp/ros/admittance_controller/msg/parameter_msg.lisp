; Auto-generated. Do not edit!


(cl:in-package admittance_controller-msg)


;//! \htmlinclude parameter_msg.msg.html

(cl:defclass <parameter_msg> (roslisp-msg-protocol:ros-message)
  ((parameter_name
    :reader parameter_name
    :initarg :parameter_name
    :type cl:string
    :initform "")
   (parameter_value
    :reader parameter_value
    :initarg :parameter_value
    :type cl:float
    :initform 0.0))
)

(cl:defclass parameter_msg (<parameter_msg>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <parameter_msg>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'parameter_msg)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name admittance_controller-msg:<parameter_msg> is deprecated: use admittance_controller-msg:parameter_msg instead.")))

(cl:ensure-generic-function 'parameter_name-val :lambda-list '(m))
(cl:defmethod parameter_name-val ((m <parameter_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader admittance_controller-msg:parameter_name-val is deprecated.  Use admittance_controller-msg:parameter_name instead.")
  (parameter_name m))

(cl:ensure-generic-function 'parameter_value-val :lambda-list '(m))
(cl:defmethod parameter_value-val ((m <parameter_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader admittance_controller-msg:parameter_value-val is deprecated.  Use admittance_controller-msg:parameter_value instead.")
  (parameter_value m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <parameter_msg>) ostream)
  "Serializes a message object of type '<parameter_msg>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'parameter_name))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'parameter_name))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'parameter_value))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <parameter_msg>) istream)
  "Deserializes a message object of type '<parameter_msg>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'parameter_name) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'parameter_name) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'parameter_value) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<parameter_msg>)))
  "Returns string type for a message object of type '<parameter_msg>"
  "admittance_controller/parameter_msg")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'parameter_msg)))
  "Returns string type for a message object of type 'parameter_msg"
  "admittance_controller/parameter_msg")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<parameter_msg>)))
  "Returns md5sum for a message object of type '<parameter_msg>"
  "2222a6ad43d45b6065719775535b8a26")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'parameter_msg)))
  "Returns md5sum for a message object of type 'parameter_msg"
  "2222a6ad43d45b6065719775535b8a26")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<parameter_msg>)))
  "Returns full string definition for message of type '<parameter_msg>"
  (cl:format cl:nil "string parameter_name~%float32 parameter_value~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'parameter_msg)))
  "Returns full string definition for message of type 'parameter_msg"
  (cl:format cl:nil "string parameter_name~%float32 parameter_value~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <parameter_msg>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'parameter_name))
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <parameter_msg>))
  "Converts a ROS message object to a list"
  (cl:list 'parameter_msg
    (cl:cons ':parameter_name (parameter_name msg))
    (cl:cons ':parameter_value (parameter_value msg))
))
