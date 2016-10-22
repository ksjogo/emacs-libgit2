(add-to-list 'load-path default-directory)

(defun libgit2-gcov-collector ()
  (libgit2-core-dump-gcov)
  (undercover-gcov-collector (file-expand-wildcards "*.gcov")))

(when (require 'undercover nil t)
  (add-to-list 'undercover-additional-files #'libgit2-gcov-collector)
  (if (getenv "TRAVIS")
      (undercover "*.el")
    (setq undercover-force-coverage t)
    (setenv "COVERALLS_REPO_TOKEN" "localrun")
    (undercover "*.el" (:report-file (expand-file-name "./coverage.json")) (:send-report nil))))

(require 'libgit2)
