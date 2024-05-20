; Auto-generated. Do not edit!


(cl:in-package admittance_controller-srv)


;//! \htmlinclude parameter_srv-request.msg.html

(cl:defclass <parameter_srv-request> (roslisp-msg-protocol:ros-message)
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

(cl:defclass parameter_srv-request (<parameter_srv-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <parameter_srv-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'parameter_srv-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name admittance_controller-srv:<parameter_srv-request> is deprecated: use admittance_controller-srv:parameter_srv-request instead.")))

(cl:ensure-generic-function 'parameter_name-val :lambda-list '(m))
(cl:defmethod parameter_name-val ((m <parameter_srv-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader admittance_controller-srv:parameter_name-val is deprecated.  Use admittance_controller-srv:parameter_name instead.")
  (parameter_name m))

(cl:ensure-generic-function 'parameter_value-val :lambda-list '(m))
(cl:defmethod parameter_value-val ((m <parameter_srv-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader admittance_controller-srv:parameter_value-val is deprecated.  Use admittance_controller-srv:parameter_value instead.")
  (parameter_value m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <parameter_srv-request>) ostream)
  "Serializes a message object of type '<parameter_srv-request>"
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
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <parameter_srv-request>) istream)
  "Deserializes a message object of type '<parameter_srv-request>"
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
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<parameter_srv-request>)))
  "Returns string type for a service object of type '<parameter_srv-request>"
  "admittance_controller/parameter_srvRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'parameter_srv-request)))
  "Returns string type for a service object of type 'parameter_srv-request"
  "admittance_controller/parameter_srvRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<parameter_srv-request>)))
  "Returns md5sum for a message object of type '<parameter_srv-request>"
  "70632979ff89b96bd0760110d8fca5c4")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'parameter_srv-request)))
  "Returns md5sum for a message object of type 'parameter_srv-request"
  "70632979ff89b96bd0760110d8fca5c4")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<parameter_srv-request>)))
  "Returns full string definition for message of type '<parameter_srv-request>"
  (cl:format cl:nil "string parameter_name~%float32 parameter_value~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'parameter_srv-request)))
  "Returns full string definition for message of type 'parameter_srv-request"
  (cl:format cl:nil "string parameter_name~%float32 parameter_value~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <parameter_srv-request>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'parameter_name))
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <parameter_srv-request>))
  "Converts a ROS message object to a list"
  (cl:list 'parameter_srv-request
    (cl:cons ':parameter_name (parameter_name msg))
    (cl:cons ':parameter_value (parameter_value msg))
))
;//! \htmlinclude parameter_srv-response.msg.html

(cl:defclass <parameter_srv-response> (roslisp-msg-protocol:ros-message)
  ((success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass parameter_srv-response (<parameter_srv-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <parameter_srv-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'parameter_srv-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name admittance_controller-srv:<parameter_srv-response> is deprecated: use admittance_controller-srv:parameter_srv-response instead.")))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <parameter_srv-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader admittance_controller-srv:success-val is deprecated.  Use admittance_controller-srv:success instead.")
  (success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <parameter_srv-response>) ostream)
  "Serializes a message object of type '<parameter_srv-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <parameter_srv-response>) istream)
  "Deserializes a message object of type '<parameter_srv-response>"
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<parameter_srv-response>)))
  "Returns string type for a service object of type '<parameter_srv-response>"
  "admittance_controller/parameter_srvResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'parameter_srv-response)))
  "Returns string type for a service object of type 'parameter_srv-response"
  "admittance_controller/parameter_srvResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<parameter_srv-response>)))
  "Returns md5sum for a message object of type '<parameter_srv-response>"
  "70632979ff89b96bd0760110d8fca5c4")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'parameter_srv-response)))
  "Returns md5sum for a message object of type 'parameter_srv-response"
  "70632979ff89b96bd0760110d8fca5c4")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<parameter_srv-response>)))
  "Returns full string definition for message of type '<parameter_srv-response>"
  (cl:format cl:nil "bool success~%~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'parameter_srv-response)))
  "Returns full string definition for message of type 'parameter_srv-response"
  (cl:format cl:nil "bool success~%~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <parameter_srv-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <parameter_srv-response>))
  "Converts a ROS message object to a list"
  (cl:list 'parameter_srv-response
    (cl:cons ':success (success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'parameter_srv)))
  'parameter_srv-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'parameter_srv)))
  'parameter_srv-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'parameter_srv)))
  "Returns string type for a service object of type '<parameter_srv>"
  "admittance_controller/parameter_srv")