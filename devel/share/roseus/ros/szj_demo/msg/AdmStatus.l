;; Auto-generated. Do not edit!


(when (boundp 'szj_demo::AdmStatus)
  (if (not (find-package "SZJ_DEMO"))
    (make-package "SZJ_DEMO"))
  (shadow 'AdmStatus (find-package "SZJ_DEMO")))
(unless (find-package "SZJ_DEMO::ADMSTATUS")
  (make-package "SZJ_DEMO::ADMSTATUS"))

(in-package "ROS")
;;//! \htmlinclude AdmStatus.msg.html


(defclass szj_demo::AdmStatus
  :super ros::object
  :slots (_forceTarget _forceNow _paraB _deltaB _zdd _commandVel _actualVel ))

(defmethod szj_demo::AdmStatus
  (:init
   (&key
    ((:forceTarget __forceTarget) 0.0)
    ((:forceNow __forceNow) 0.0)
    ((:paraB __paraB) 0.0)
    ((:deltaB __deltaB) 0.0)
    ((:zdd __zdd) 0.0)
    ((:commandVel __commandVel) 0.0)
    ((:actualVel __actualVel) 0.0)
    )
   (send-super :init)
   (setq _forceTarget (float __forceTarget))
   (setq _forceNow (float __forceNow))
   (setq _paraB (float __paraB))
   (setq _deltaB (float __deltaB))
   (setq _zdd (float __zdd))
   (setq _commandVel (float __commandVel))
   (setq _actualVel (float __actualVel))
   self)
  (:forceTarget
   (&optional __forceTarget)
   (if __forceTarget (setq _forceTarget __forceTarget)) _forceTarget)
  (:forceNow
   (&optional __forceNow)
   (if __forceNow (setq _forceNow __forceNow)) _forceNow)
  (:paraB
   (&optional __paraB)
   (if __paraB (setq _paraB __paraB)) _paraB)
  (:deltaB
   (&optional __deltaB)
   (if __deltaB (setq _deltaB __deltaB)) _deltaB)
  (:zdd
   (&optional __zdd)
   (if __zdd (setq _zdd __zdd)) _zdd)
  (:commandVel
   (&optional __commandVel)
   (if __commandVel (setq _commandVel __commandVel)) _commandVel)
  (:actualVel
   (&optional __actualVel)
   (if __actualVel (setq _actualVel __actualVel)) _actualVel)
  (:serialization-length
   ()
   (+
    ;; float64 _forceTarget
    8
    ;; float64 _forceNow
    8
    ;; float64 _paraB
    8
    ;; float64 _deltaB
    8
    ;; float64 _zdd
    8
    ;; float64 _commandVel
    8
    ;; float64 _actualVel
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float64 _forceTarget
       (sys::poke _forceTarget (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _forceNow
       (sys::poke _forceNow (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _paraB
       (sys::poke _paraB (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _deltaB
       (sys::poke _deltaB (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _zdd
       (sys::poke _zdd (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _commandVel
       (sys::poke _commandVel (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _actualVel
       (sys::poke _actualVel (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float64 _forceTarget
     (setq _forceTarget (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _forceNow
     (setq _forceNow (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _paraB
     (setq _paraB (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _deltaB
     (setq _deltaB (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _zdd
     (setq _zdd (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _commandVel
     (setq _commandVel (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _actualVel
     (setq _actualVel (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get szj_demo::AdmStatus :md5sum-) "0eec79276a71eca81aff53272305516b")
(setf (get szj_demo::AdmStatus :datatype-) "szj_demo/AdmStatus")
(setf (get szj_demo::AdmStatus :definition-)
      "float64 forceTarget
float64 forceNow
float64 paraB
float64 deltaB
float64 zdd
float64 commandVel
float64 actualVel
")



(provide :szj_demo/AdmStatus "0eec79276a71eca81aff53272305516b")


