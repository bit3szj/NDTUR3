;; Auto-generated. Do not edit!


(when (boundp 'admittance_controller::joint_trajectory)
  (if (not (find-package "ADMITTANCE_CONTROLLER"))
    (make-package "ADMITTANCE_CONTROLLER"))
  (shadow 'joint_trajectory (find-package "ADMITTANCE_CONTROLLER")))
(unless (find-package "ADMITTANCE_CONTROLLER::JOINT_TRAJECTORY")
  (make-package "ADMITTANCE_CONTROLLER::JOINT_TRAJECTORY"))

(in-package "ROS")
;;//! \htmlinclude joint_trajectory.msg.html
(if (not (find-package "SENSOR_MSGS"))
  (ros::roseus-add-msgs "sensor_msgs"))


(defclass admittance_controller::joint_trajectory
  :super ros::object
  :slots (_trajectory _extra_data _velocity_scaling_percentage ))

(defmethod admittance_controller::joint_trajectory
  (:init
   (&key
    ((:trajectory __trajectory) ())
    ((:extra_data __extra_data) ())
    ((:velocity_scaling_percentage __velocity_scaling_percentage) 0)
    )
   (send-super :init)
   (setq _trajectory __trajectory)
   (setq _extra_data __extra_data)
   (setq _velocity_scaling_percentage (round __velocity_scaling_percentage))
   self)
  (:trajectory
   (&rest __trajectory)
   (if (keywordp (car __trajectory))
       (send* _trajectory __trajectory)
     (progn
       (if __trajectory (setq _trajectory (car __trajectory)))
       _trajectory)))
  (:extra_data
   (&rest __extra_data)
   (if (keywordp (car __extra_data))
       (send* _extra_data __extra_data)
     (progn
       (if __extra_data (setq _extra_data (car __extra_data)))
       _extra_data)))
  (:velocity_scaling_percentage
   (&optional __velocity_scaling_percentage)
   (if __velocity_scaling_percentage (setq _velocity_scaling_percentage __velocity_scaling_percentage)) _velocity_scaling_percentage)
  (:serialization-length
   ()
   (+
    ;; sensor_msgs/JointState[] _trajectory
    (apply #'+ (send-all _trajectory :serialization-length)) 4
    ;; admittance_controller/parameter_msg[] _extra_data
    (apply #'+ (send-all _extra_data :serialization-length)) 4
    ;; int64 _velocity_scaling_percentage
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; sensor_msgs/JointState[] _trajectory
     (write-long (length _trajectory) s)
     (dolist (elem _trajectory)
       (send elem :serialize s)
       )
     ;; admittance_controller/parameter_msg[] _extra_data
     (write-long (length _extra_data) s)
     (dolist (elem _extra_data)
       (send elem :serialize s)
       )
     ;; int64 _velocity_scaling_percentage
#+(or :alpha :irix6 :x86_64)
       (progn (sys::poke _velocity_scaling_percentage (send s :buffer) (send s :count) :long) (incf (stream-count s) 8))
#-(or :alpha :irix6 :x86_64)
       (cond ((and (class _velocity_scaling_percentage) (= (length (_velocity_scaling_percentage . bv)) 2)) ;; bignum
              (write-long (ash (elt (_velocity_scaling_percentage . bv) 0) 0) s)
              (write-long (ash (elt (_velocity_scaling_percentage . bv) 1) -1) s))
             ((and (class _velocity_scaling_percentage) (= (length (_velocity_scaling_percentage . bv)) 1)) ;; big1
              (write-long (elt (_velocity_scaling_percentage . bv) 0) s)
              (write-long (if (>= _velocity_scaling_percentage 0) 0 #xffffffff) s))
             (t                                         ;; integer
              (write-long _velocity_scaling_percentage s)(write-long (if (>= _velocity_scaling_percentage 0) 0 #xffffffff) s)))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; sensor_msgs/JointState[] _trajectory
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _trajectory (let (r) (dotimes (i n) (push (instance sensor_msgs::JointState :init) r)) r))
     (dolist (elem- _trajectory)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;; admittance_controller/parameter_msg[] _extra_data
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _extra_data (let (r) (dotimes (i n) (push (instance admittance_controller::parameter_msg :init) r)) r))
     (dolist (elem- _extra_data)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;; int64 _velocity_scaling_percentage
#+(or :alpha :irix6 :x86_64)
      (setf _velocity_scaling_percentage (prog1 (sys::peek buf ptr- :long) (incf ptr- 8)))
#-(or :alpha :irix6 :x86_64)
      (setf _velocity_scaling_percentage (let ((b0 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4)))
                  (b1 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4))))
              (cond ((= b1 -1) b0)
                     ((and (= b1  0)
                           (<= lisp::most-negative-fixnum b0 lisp::most-positive-fixnum))
                      b0)
                    ((= b1  0) (make-instance bignum :size 1 :bv (integer-vector b0)))
                    (t (make-instance bignum :size 2 :bv (integer-vector b0 (ash b1 1)))))))
   ;;
   self)
  )

(setf (get admittance_controller::joint_trajectory :md5sum-) "9047f34bd5bbdb3efed33b5595650679")
(setf (get admittance_controller::joint_trajectory :datatype-) "admittance_controller/joint_trajectory")
(setf (get admittance_controller::joint_trajectory :definition-)
      "sensor_msgs/JointState[] trajectory
parameter_msg[] extra_data
int64 velocity_scaling_percentage

================================================================================
MSG: sensor_msgs/JointState
# This is a message that holds data to describe the state of a set of torque controlled joints. 
#
# The state of each joint (revolute or prismatic) is defined by:
#  * the position of the joint (rad or m),
#  * the velocity of the joint (rad/s or m/s) and 
#  * the effort that is applied in the joint (Nm or N).
#
# Each joint is uniquely identified by its name
# The header specifies the time at which the joint states were recorded. All the joint states
# in one message have to be recorded at the same time.
#
# This message consists of a multiple arrays, one for each part of the joint state. 
# The goal is to make each of the fields optional. When e.g. your joints have no
# effort associated with them, you can leave the effort array empty. 
#
# All arrays in this message should have the same size, or be empty.
# This is the only way to uniquely associate the joint name with the correct
# states.


Header header

string[] name
float64[] position
float64[] velocity
float64[] effort

================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
string frame_id

================================================================================
MSG: admittance_controller/parameter_msg
string parameter_name
float32 parameter_value

")



(provide :admittance_controller/joint_trajectory "9047f34bd5bbdb3efed33b5595650679")


