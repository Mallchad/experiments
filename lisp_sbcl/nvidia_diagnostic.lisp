#!/usr/bin/env -S sbcl --script

;; (run-program "/bin/bash" :ARGUMENTS '("-c" "while [ 1 ] ; do ; nvidia-smi --query --xml-format ; sleep 0.001 ; done "))

(defun main ()
    (sb-ext:run-program "/usr/bin/nvidia-smi" '("--query" "--xml-format")
     :output *standard-output*)
)
(main)
(exit)
