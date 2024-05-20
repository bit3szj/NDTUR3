;; Auto-generated. Do not edit!


(when (boundp 'admittance_controller::parameter_srv)
  (if (not (find-package "ADMITTANCE_CONTROLLER"))
    (make-package "ADMITTANCE_CONTROLLER"))
  (shadow 'parameter_srv (find-package "ADMITTANCE_CONTROLLER")))
(unless (find-package "ADMITTANCE_CONTROLLER::PARAMETER_SRV")
  (make-package "ADMITTANCE_CONTROLLER::PARAMETER_SRV"))
(unless (find-package "ADMITTANCE_CONTROLLER::PARAMETER_SRVREQUEST")
  (make-package "ADMITTANCE_CONTROLLER::PARAMETER_SRVREQUEST"))
(unless (find-package "ADMITTANCE_CONTROLLER::PARAMETER_SRVRESPONSE")
  (make-package "ADMITTANCE_CONTROLLER::PARAMETER_SRVRESPONSE"))

(in-package "ROS")





(defclass admittance_controller::parameter_srvRequest
  :super ros::object
  :slots (_parameter_name _parameter_value ))

(defmethod admittance_controller::parameter_srvRequest
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

(defclass admittance_controller::parameter_srvResponse
  :super ros::object
  :slots (_success ))

(defmethod admittance_controller::parameter_srvResponse
  (:init
   (&key
    ((:success __success) nil)
    )
   (send-super :init)
   (setq _success __success)
   self)
  (:success
   (&optional (__success :null))
   (if (not (eq __success :null)) (setq _success __success)) _success)
  (:serialization-length
   ()
   (+
    ;; bool _success
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _success
       (if _success (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _success
     (setq _success (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass admittance_controller::parameter_srv
  :super ros::object
  :slots ())

(setf (get admittance_controller::parameter_srv :md5sum-) "70632979ff89b96bd0760110d8fca5c4")
(setf (get admittance_controller::parameter_srv :datatype-) "admittance_controller/parameter_srv")
(setf (get admittance_controller::parameter_srv :request) admittance_controller::parameter_srvRequest)
(setf (get admittance_controller::parameter_srv :response) admittance_controller::parameter_srvResponse)

(defmethod admittance_controller::parameter_srvRequest
  (:response () (instance admittance_controller::parameter_srvResponse :init)))

(setf (get admittance_controller::parameter_srvRequest :md5sum-) "70632979ff89b96bd0760110d8fca5c4")
(setf (get admittance_controller::parameter_srvRequest :datatype-) "admittance_controller/parameter_srvRequest")
(setf (get admittance_controller::parameter_srvRequest :definition-)
      "string parameter_name
float32 parameter_value
---
bool success


")

(setf (get admittance_controller::parameter_srvResponse :md5sum-) "70632979ff89b96bd0760110d8fca5c4")
(setf (get admittance_controller::parameter_srvResponse :datatype-) "admittance_controller/parameter_srvResponse")
(setf (get admittance_controller::parameter_srvResponse :definition-)
      "string parameter_name
float32 parameter_value
---
bool success


")



(provide :admittance_controller/parameter_srv "70632979ff89b96bd0760110d8fca5c4")


