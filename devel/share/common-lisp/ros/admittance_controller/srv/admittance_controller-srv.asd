
(cl:in-package :asdf)

(defsystem "admittance_controller-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "parameter_srv" :depends-on ("_package_parameter_srv"))
    (:file "_package_parameter_srv" :depends-on ("_package"))
  ))