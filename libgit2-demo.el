#!/usr/bin/env emacs --script

;;; fswatch -o libgit2-core.so -o libgit2-demo.el | xargs -n1 ./libgit2-demo.el

(add-to-list 'load-path ".")
(require 'libgit2-core)

(require 'package)
(require 'magit)
(require 'pp)

(defmacro time-it (form)
  "Time and report the duration of FORM."
  (let* ((fmt1 (format "Timing `%S'..." (car form)))
         (fmt2 (concat fmt1 "done (%ss)")))
    `(prog2 (progn (message ,fmt1)
                   (setq *time-start* (current-time)))
         (let ((result ,form))
           (message ,fmt2 (time-to-seconds (time-subtract (current-time) *time-start*)))
           (message "Form evaluated to: %s" (pp-to-string result))))))

(let ((repo (expand-file-name "./testrepo")))

  (time-it (libgit2-core-status repo))

  (message
   "Benchmark L/C: %s"
   (let ((c-times (car (benchmark-run 1000 (libgit2-core-get-current-branch repo))))
         (l-times (car (benchmark-run 1000 (magit-get-current-branch)))))
     (message "Benchmark C: %ss"    c-times)
     (message "Benchmark Lisp: %ss" l-times)
     (/ l-times c-times)))

  (message "Demo complete!"))
