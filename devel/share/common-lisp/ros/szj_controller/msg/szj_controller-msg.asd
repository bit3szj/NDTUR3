
(cl:in-package :asdf)

(defsystem "szj_controller-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "pointData" :depends-on ("_package_pointData"))
    (:file "_package_pointData" :depends-on ("_package"))
  ))