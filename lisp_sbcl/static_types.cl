

(defun main ()
    (setq num 1)
    (+ num "error")
    )

(sb-ext:save-lisp-and-die "static_types" :executable t :toplevel 'main)
