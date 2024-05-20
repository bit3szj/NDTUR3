
(cl:in-package :asdf)

(defsystem "szj_demo-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "AdmStatus" :depends-on ("_package_AdmStatus"))
    (:file "_package_AdmStatus" :depends-on ("_package"))
    (:file "toolStatus" :depends-on ("_package_toolStatus"))
    (:file "_package_toolStatus" :depends-on ("_package"))
  ))