(run-program "/bin/bash" :ARGUMENTS '("-c" "while [ 1 ] ; do ; nvidia-smi --query --xml-format ; sleep 0.001 ; done "))
;; (run-program "/usr/bin/nvidia-smi" :ARGUMENTS '("--query" "--xml-format"))