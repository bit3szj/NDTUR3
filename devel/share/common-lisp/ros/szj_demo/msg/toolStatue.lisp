; Auto-generated. Do not edit!


(cl:in-package szj_demo-msg)


;//! \htmlinclude toolStatue.msg.html

(cl:defclass <toolStatue> (roslisp-msg-protocol:ros-message)
  ((linearX
    :reader linearX
    :initarg :linearX
    :type cl:float
    :initform 0.0)
   (linearY
    :reader linearY
    :initarg :linearY
    :type cl:float
    :initform 0.0)
   (linearZ
    :reader linearZ
    :initarg :linearZ
    :type cl:float
    :initform 0.0)
   (angularX
    :reader angularX
    :initarg :angularX
    :type cl:float
    :initform 0.0)
   (angularY
    :reader angularY
    :initarg :angularY
    :type cl:float
    :initform 0.0)
   (angularZ
    :reader angularZ
    :initarg :angularZ
    :type cl:float
    :initform 0.0)
   (velLinearX
    :reader velLinearX
    :initarg :velLinearX
    :type cl:float
    :initform 0.0)
   (velLinearY
    :reader velLinearY
    :initarg :velLinearY
    :type cl:float
    :initform 0.0)
   (velLinearZ
    :reader velLinearZ
    :initarg :velLinearZ
    :type cl:float
    :initform 0.0)
   (velAngularX
    :reader velAngularX
    :initarg :velAngularX
    :type cl:float
    :initform 0.0)
   (velAngularY
    :reader velAngularY
    :initarg :velAngularY
    :type cl:float
    :initform 0.0)
   (velAngularZ
    :reader velAngularZ
    :initarg :velAngularZ
    :type cl:float
    :initform 0.0))
)

(cl:defclass toolStatue (<toolStatue>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <toolStatue>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'toolStatue)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name szj_demo-msg:<toolStatue> is deprecated: use szj_demo-msg:toolStatue instead.")))

(cl:ensure-generic-function 'linearX-val :lambda-list '(m))
(cl:defmethod linearX-val ((m <toolStatue>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader szj_demo-msg:linearX-val is deprecated.  Use szj_demo-msg:linearX instead.")
  (linearX m))

(cl:ensure-generic-function 'linearY-val :lambda-list '(m))
(cl:defmethod linearY-val ((m <toolStatue>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader szj_demo-msg:linearY-val is deprecated.  Use szj_demo-msg:linearY instead.")
  (linearY m))

(cl:ensure-generic-function 'linearZ-val :lambda-list '(m))
(cl:defmethod linearZ-val ((m <toolStatue>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader szj_demo-msg:linearZ-val is deprecated.  Use szj_demo-msg:linearZ instead.")
  (linearZ m))

(cl:ensure-generic-function 'angularX-val :lambda-list '(m))
(cl:defmethod angularX-val ((m <toolStatue>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader szj_demo-msg:angularX-val is deprecated.  Use szj_demo-msg:angularX instead.")
  (angularX m))

(cl:ensure-generic-function 'angularY-val :lambda-list '(m))
(cl:defmethod angularY-val ((m <toolStatue>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader szj_demo-msg:angularY-val is deprecated.  Use szj_demo-msg:angularY instead.")
  (angularY m))

(cl:ensure-generic-function 'angularZ-val :lambda-list '(m))
(cl:defmethod angularZ-val ((m <toolStatue>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader szj_demo-msg:angularZ-val is deprecated.  Use szj_demo-msg:angularZ instead.")
  (angularZ m))

(cl:ensure-generic-function 'velLinearX-val :lambda-list '(m))
(cl:defmethod velLinearX-val ((m <toolStatue>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader szj_demo-msg:velLinearX-val is deprecated.  Use szj_demo-msg:velLinearX instead.")
  (velLinearX m))

(cl:ensure-generic-function 'velLinearY-val :lambda-list '(m))
(cl:defmethod velLinearY-val ((m <toolStatue>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader szj_demo-msg:velLinearY-val is deprecated.  Use szj_demo-msg:velLinearY instead.")
  (velLinearY m))

(cl:ensure-generic-function 'velLinearZ-val :lambda-list '(m))
(cl:defmethod velLinearZ-val ((m <toolStatue>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader szj_demo-msg:velLinearZ-val is deprecated.  Use szj_demo-msg:velLinearZ instead.")
  (velLinearZ m))

(cl:ensure-generic-function 'velAngularX-val :lambda-list '(m))
(cl:defmethod velAngularX-val ((m <toolStatue>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader szj_demo-msg:velAngularX-val is deprecated.  Use szj_demo-msg:velAngularX instead.")
  (velAngularX m))

(cl:ensure-generic-function 'velAngularY-val :lambda-list '(m))
(cl:defmethod velAngularY-val ((m <toolStatue>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader szj_demo-msg:velAngularY-val is deprecated.  Use szj_demo-msg:velAngularY instead.")
  (velAngularY m))

(cl:ensure-generic-function 'velAngularZ-val :lambda-list '(m))
(cl:defmethod velAngularZ-val ((m <toolStatue>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader szj_demo-msg:velAngularZ-val is deprecated.  Use szj_demo-msg:velAngularZ instead.")
  (velAngularZ m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <toolStatue>) ostream)
  "Serializes a message object of type '<toolStatue>"
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'linearX))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'linearY))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'linearZ))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'angularX))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'angularY))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'angularZ))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'velLinearX))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'velLinearY))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'velLinearZ))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'velAngularX))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'velAngularY))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'velAngularZ))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <toolStatue>) istream)
  "Deserializes a message object of type '<toolStatue>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'linearX) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'linearY) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'linearZ) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'angularX) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'angularY) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'angularZ) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'velLinearX) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'velLinearY) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'velLinearZ) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'velAngularX) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'velAngularY) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'velAngularZ) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<toolStatue>)))
  "Returns string type for a message object of type '<toolStatue>"
  "szj_demo/toolStatue")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'toolStatue)))
  "Returns string type for a message object of type 'toolStatue"
  "szj_demo/toolStatue")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<toolStatue>)))
  "Returns md5sum for a message object of type '<toolStatue>"
  "fc2d79cf8b7f949061e6ffc3b214e01e")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'toolStatue)))
  "Returns md5sum for a message object of type 'toolStatue"
  "fc2d79cf8b7f949061e6ffc3b214e01e")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<toolStatue>)))
  "Returns full string definition for message of type '<toolStatue>"
  (cl:format cl:nil "float64 linearX~%float64 linearY~%float64 linearZ~%float64 angularX~%float64 angularY~%float64 angularZ~%float64 velLinearX~%float64 velLinearY~%float64 velLinearZ~%float64 velAngularX~%float64 velAngularY~%float64 velAngularZ~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'toolStatue)))
  "Returns full string definition for message of type 'toolStatue"
  (cl:format cl:nil "float64 linearX~%float64 linearY~%float64 linearZ~%float64 angularX~%float64 angularY~%float64 angularZ~%float64 velLinearX~%float64 velLinearY~%float64 velLinearZ~%float64 velAngularX~%float64 velAngularY~%float64 velAngularZ~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <toolStatue>))
  (cl:+ 0
     8
     8
     8
     8
     8
     8
     8
     8
     8
     8
     8
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <toolStatue>))
  "Converts a ROS message object to a list"
  (cl:list 'toolStatue
    (cl:cons ':linearX (linearX msg))
    (cl:cons ':linearY (linearY msg))
    (cl:cons ':linearZ (linearZ msg))
    (cl:cons ':angularX (angularX msg))
    (cl:cons ':angularY (angularY msg))
    (cl:cons ':angularZ (angularZ msg))
    (cl:cons ':velLinearX (velLinearX msg))
    (cl:cons ':velLinearY (velLinearY msg))
    (cl:cons ':velLinearZ (velLinearZ msg))
    (cl:cons ':velAngularX (velAngularX msg))
    (cl:cons ':velAngularY (velAngularY msg))
    (cl:cons ':velAngularZ (velAngularZ msg))
))
