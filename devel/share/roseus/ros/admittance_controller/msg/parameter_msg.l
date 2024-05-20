;; Auto-generated. Do not edit!


(when (boundp 'admittance_controller::parameter_msg)
  (if (not (find-package "ADMITTANCE_CONTROLLER"))
    (make-package "ADMITTANCE_CONTROLLER"))
  (shadow 'parameter_msg (find-package "ADMITTANCE_CONTROLLER")))
(unless (find-package "ADMITTANCE_CONTROLLER::PARAMETER_MSG")
  (make-package "ADMITTANCE_CONTROLLER::PARAMETER_MSG"))

(in-package "ROS")
;;//! \htmlinclude parameter_msg.msg.html


(defclass admittance_controller::parameter_msg
  :super ros::object
  :slots (_parameter_name _parameter_value ))

(defmethod admittance_controller::parameter_msg
  (:init
   (&key
    ((:parameter_name __parameter_name) "")
    ((:parameter_value __parameter_value) 0.0)
    )
   (send-super :init)
   (setq _parameter_name (string __parameter_name))
   (setq _parameter_value (float __parameter_value))
   self)
  (:parameter_name
   (&optional __parameter_name)
   (if __parameter_name (setq _parameter_name __parameter_name)) _parameter_name)
  (:parameter_value
   (&optional __parameter_value)
   (if __parameter_value (setq _parameter_value __parameter_value)) _parameter_value)
  (:serialization-length
   ()
   (+
    ;; string _parameter_name
    4 (length _parameter_name)
    ;; float32 _parameter_value
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _parameter_name
       (write-long (length _parameter_name) s) (princ _parameter_name s)
     ;; float32 _parameter_value
       (sys::poke _parameter_value (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _parameter_name
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _parameter_name (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; float32 _parameter_value
     (setq _parameter_value (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get admittance_controller::parameter_msg :md5sum-) "2222a6ad43d45b6065719775535b8a26")
(setf (get admittance_controller::parameter_msg :datatype-) "admittance_controller/parameter_msg")
(setf (get admittance_controller::parameter_msg :definition-)
      "string parameter_name
float32 parameter_value

")



(provide :admittance_controller/parameter_msg "2222a6ad43d45b6065719775535b8a26")


