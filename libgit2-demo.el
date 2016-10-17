#!/usr/bin/env emacs --script

;;; fswatch -o libgit2-core.so -o libgit2-demo.el | xargs -n1 ./libgit2-demo.el

(add-to-list 'load-path ".")
(require 'libgit2-core)
(package-initialize)
(require 'magit)

(defmacro time-it (form)
  "Time and report the duration of FORM."
  (let* ((fmt1 (format "Timing `%S'..." (car form)))
         (fmt2 (concat fmt1 "done (%ss)")))
    `(prog2 (progn (message ,fmt1)
                   (setq *time-start* (current-time)))
         ,form
       (message ,fmt2 (time-to-seconds (time-subtract (current-time) *time-start*))))))

(time-it (libgit2-core-status (expand-file-name ".")))

(message
 "Benchmark L/C: %s"
 (let* ((fn (expand-file-name "."))
        (c-times (car (benchmark-run 1000 (libgit2-core-current-branch fn))))
        (l-times (car (benchmark-run 1000 (magit-get-current-branch)))))
   (message "Benchmark C: %ss"    c-times)
   (message "Benchmark Lisp: %ss" l-times)
   (/ l-times c-times)))

(message "Demo complete!")
