#!/usr/bin/env -S sbcl --script

(defun main ()
  (declare (type integer num))
  (let (num)

    (setq num 1)
    ;; (+ num "error")
    (+ num 2)
    )
  (print "test")
  (ensure-directories-exist  "/home/mallchad/tmp/lisp1" :verbose t)
  )

(main)
(ensure-directories-exist  "/home/mallchad/tmp/lisp1" :verbose t)

(print "rawr")
(sb-ext:save-lisp-and-die "build/static_types" :executable t :toplevel 'main)
