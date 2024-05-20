; Auto-generated. Do not edit!


(cl:in-package szj_demo-msg)


;//! \htmlinclude AdmStatus.msg.html

(cl:defclass <AdmStatus> (roslisp-msg-protocol:ros-message)
  ((forceTarget
    :reader forceTarget
    :initarg :forceTarget
    :type cl:float
    :initform 0.0)
   (forceNow
    :reader forceNow
    :initarg :forceNow
    :type cl:float
    :initform 0.0)
   (paraB
    :reader paraB
    :initarg :paraB
    :type cl:float
    :initform 0.0)
   (deltaB
    :reader deltaB
    :initarg :deltaB
    :type cl:float
    :initform 0.0)
   (zdd
    :reader zdd
    :initarg :zdd
    :type cl:float
    :initform 0.0)
   (commandVel
    :reader commandVel
    :initarg :commandVel
    :type cl:float
    :initform 0.0)
   (actualVel
    :reader actualVel
    :initarg :actualVel
    :type cl:float
    :initform 0.0))
)

(cl:defclass AdmStatus (<AdmStatus>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <AdmStatus>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'AdmStatus)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name szj_demo-msg:<AdmStatus> is deprecated: use szj_demo-msg:AdmStatus instead.")))

(cl:ensure-generic-function 'forceTarget-val :lambda-list '(m))
(cl:defmethod forceTarget-val ((m <AdmStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader szj_demo-msg:forceTarget-val is deprecated.  Use szj_demo-msg:forceTarget instead.")
  (forceTarget m))

(cl:ensure-generic-function 'forceNow-val :lambda-list '(m))
(cl:defmethod forceNow-val ((m <AdmStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader szj_demo-msg:forceNow-val is deprecated.  Use szj_demo-msg:forceNow instead.")
  (forceNow m))

(cl:ensure-generic-function 'paraB-val :lambda-list '(m))
(cl:defmethod paraB-val ((m <AdmStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader szj_demo-msg:paraB-val is deprecated.  Use szj_demo-msg:paraB instead.")
  (paraB m))

(cl:ensure-generic-function 'deltaB-val :lambda-list '(m))
(cl:defmethod deltaB-val ((m <AdmStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader szj_demo-msg:deltaB-val is deprecated.  Use szj_demo-msg:deltaB instead.")
  (deltaB m))

(cl:ensure-generic-function 'zdd-val :lambda-list '(m))
(cl:defmethod zdd-val ((m <AdmStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader szj_demo-msg:zdd-val is deprecated.  Use szj_demo-msg:zdd instead.")
  (zdd m))

(cl:ensure-generic-function 'commandVel-val :lambda-list '(m))
(cl:defmethod commandVel-val ((m <AdmStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader szj_demo-msg:commandVel-val is deprecated.  Use szj_demo-msg:commandVel instead.")
  (commandVel m))

(cl:ensure-generic-function 'actualVel-val :lambda-list '(m))
(cl:defmethod actualVel-val ((m <AdmStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader szj_demo-msg:actualVel-val is deprecated.  Use szj_demo-msg:actualVel instead.")
  (actualVel m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <AdmStatus>) ostream)
  "Serializes a message object of type '<AdmStatus>"
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'forceTarget))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'forceNow))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'paraB))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'deltaB))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'zdd))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'commandVel))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'actualVel))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <AdmStatus>) istream)
  "Deserializes a message object of type '<AdmStatus>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'forceTarget) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'forceNow) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'paraB) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'deltaB) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'zdd) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'commandVel) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'actualVel) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<AdmStatus>)))
  "Returns string type for a message object of type '<AdmStatus>"
  "szj_demo/AdmStatus")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'AdmStatus)))
  "Returns string type for a message object of type 'AdmStatus"
  "szj_demo/AdmStatus")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<AdmStatus>)))
  "Returns md5sum for a message object of type '<AdmStatus>"
  "0eec79276a71eca81aff53272305516b")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'AdmStatus)))
  "Returns md5sum for a message object of type 'AdmStatus"
  "0eec79276a71eca81aff53272305516b")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<AdmStatus>)))
  "Returns full string definition for message of type '<AdmStatus>"
  (cl:format cl:nil "float64 forceTarget~%float64 forceNow~%float64 paraB~%float64 deltaB~%float64 zdd~%float64 commandVel~%float64 actualVel~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'AdmStatus)))
  "Returns full string definition for message of type 'AdmStatus"
  (cl:format cl:nil "float64 forceTarget~%float64 forceNow~%float64 paraB~%float64 deltaB~%float64 zdd~%float64 commandVel~%float64 actualVel~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <AdmStatus>))
  (cl:+ 0
     8
     8
     8
     8
     8
     8
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <AdmStatus>))
  "Converts a ROS message object to a list"
  (cl:list 'AdmStatus
    (cl:cons ':forceTarget (forceTarget msg))
    (cl:cons ':forceNow (forceNow msg))
    (cl:cons ':paraB (paraB msg))
    (cl:cons ':deltaB (deltaB msg))
    (cl:cons ':zdd (zdd msg))
    (cl:cons ':commandVel (commandVel msg))
    (cl:cons ':actualVel (actualVel msg))
))
