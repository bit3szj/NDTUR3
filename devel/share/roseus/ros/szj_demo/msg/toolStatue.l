;; Auto-generated. Do not edit!


(when (boundp 'szj_demo::toolStatue)
  (if (not (find-package "SZJ_DEMO"))
    (make-package "SZJ_DEMO"))
  (shadow 'toolStatue (find-package "SZJ_DEMO")))
(unless (find-package "SZJ_DEMO::TOOLSTATUE")
  (make-package "SZJ_DEMO::TOOLSTATUE"))

(in-package "ROS")
;;//! \htmlinclude toolStatue.msg.html


(defclass szj_demo::toolStatue
  :super ros::object
  :slots (_linearX _linearY _linearZ _angularX _angularY _angularZ _velLinearX _velLinearY _velLinearZ _velAngularX _velAngularY _velAngularZ ))

(defmethod szj_demo::toolStatue
  (:init
   (&key
    ((:linearX __linearX) 0.0)
    ((:linearY __linearY) 0.0)
    ((:linearZ __linearZ) 0.0)
    ((:angularX __angularX) 0.0)
    ((:angularY __angularY) 0.0)
    ((:angularZ __angularZ) 0.0)
    ((:velLinearX __velLinearX) 0.0)
    ((:velLinearY __velLinearY) 0.0)
    ((:velLinearZ __velLinearZ) 0.0)
    ((:velAngularX __velAngularX) 0.0)
    ((:velAngularY __velAngularY) 0.0)
    ((:velAngularZ __velAngularZ) 0.0)
    )
   (send-super :init)
   (setq _linearX (float __linearX))
   (setq _linearY (float __linearY))
   (setq _linearZ (float __linearZ))
   (setq _angularX (float __angularX))
   (setq _angularY (float __angularY))
   (setq _angularZ (float __angularZ))
   (setq _velLinearX (float __velLinearX))
   (setq _velLinearY (float __velLinearY))
   (setq _velLinearZ (float __velLinearZ))
   (setq _velAngularX (float __velAngularX))
   (setq _velAngularY (float __velAngularY))
   (setq _velAngularZ (float __velAngularZ))
   self)
  (:linearX
   (&optional __linearX)
   (if __linearX (setq _linearX __linearX)) _linearX)
  (:linearY
   (&optional __linearY)
   (if __linearY (setq _linearY __linearY)) _linearY)
  (:linearZ
   (&optional __linearZ)
   (if __linearZ (setq _linearZ __linearZ)) _linearZ)
  (:angularX
   (&optional __angularX)
   (if __angularX (setq _angularX __angularX)) _angularX)
  (:angularY
   (&optional __angularY)
   (if __angularY (setq _angularY __angularY)) _angularY)
  (:angularZ
   (&optional __angularZ)
   (if __angularZ (setq _angularZ __angularZ)) _angularZ)
  (:velLinearX
   (&optional __velLinearX)
   (if __velLinearX (setq _velLinearX __velLinearX)) _velLinearX)
  (:velLinearY
   (&optional __velLinearY)
   (if __velLinearY (setq _velLinearY __velLinearY)) _velLinearY)
  (:velLinearZ
   (&optional __velLinearZ)
   (if __velLinearZ (setq _velLinearZ __velLinearZ)) _velLinearZ)
  (:velAngularX
   (&optional __velAngularX)
   (if __velAngularX (setq _velAngularX __velAngularX)) _velAngularX)
  (:velAngularY
   (&optional __velAngularY)
   (if __velAngularY (setq _velAngularY __velAngularY)) _velAngularY)
  (:velAngularZ
   (&optional __velAngularZ)
   (if __velAngularZ (setq _velAngularZ __velAngularZ)) _velAngularZ)
  (:serialization-length
   ()
   (+
    ;; float64 _linearX
    8
    ;; float64 _linearY
    8
    ;; float64 _linearZ
    8
    ;; float64 _angularX
    8
    ;; float64 _angularY
    8
    ;; float64 _angularZ
    8
    ;; float64 _velLinearX
    8
    ;; float64 _velLinearY
    8
    ;; float64 _velLinearZ
    8
    ;; float64 _velAngularX
    8
    ;; float64 _velAngularY
    8
    ;; float64 _velAngularZ
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _linearX
       (sys::poke _linearX (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _linearY
       (sys::poke _linearY (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _linearZ
       (sys::poke _linearZ (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _angularX
       (sys::poke _angularX (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _angularY
       (sys::poke _angularY (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _angularZ
       (sys::poke _angularZ (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _velLinearX
       (sys::poke _velLinearX (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _velLinearY
       (sys::poke _velLinearY (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _velLinearZ
       (sys::poke _velLinearZ (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _velAngularX
       (sys::poke _velAngularX (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _velAngularY
       (sys::poke _velAngularY (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _velAngularZ
       (sys::poke _velAngularZ (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _linearX
     (setq _linearX (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _linearY
     (setq _linearY (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _linearZ
     (setq _linearZ (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _angularX
     (setq _angularX (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _angularY
     (setq _angularY (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _angularZ
     (setq _angularZ (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _velLinearX
     (setq _velLinearX (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _velLinearY
     (setq _velLinearY (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _velLinearZ
     (setq _velLinearZ (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _velAngularX
     (setq _velAngularX (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _velAngularY
     (setq _velAngularY (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _velAngularZ
     (setq _velAngularZ (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get szj_demo::toolStatue :md5sum-) "fc2d79cf8b7f949061e6ffc3b214e01e")
(setf (get szj_demo::toolStatue :datatype-) "szj_demo/toolStatue")
(setf (get szj_demo::toolStatue :definition-)
      "float64 linearX
float64 linearY
float64 linearZ
float64 angularX
float64 angularY
float64 angularZ
float64 velLinearX
float64 velLinearY
float64 velLinearZ
float64 velAngularX
float64 velAngularY
float64 velAngularZ
")



(provide :szj_demo/toolStatue "fc2d79cf8b7f949061e6ffc3b214e01e")


