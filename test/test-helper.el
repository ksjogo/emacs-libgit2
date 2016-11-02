(add-to-list 'load-path default-directory)

(defun libgit2-gcov-collector ()
  (libgit2-core-dump-gcov)
  (pp (shell-command-to-string "gcov -o CMakeFiles/git2-core.dir/ CMakeFiles/git2-core.dir/*.o"))
  (pp (file-expand-wildcards "*.gcov"))
  (undercover-gcov-collector (file-expand-wildcards "*.gcov")))

(when (require 'undercover nil t)
  (add-to-list 'undercover-additional-files #'libgit2-gcov-collector)
  (if (getenv "TRAVIS")
      (undercover "*.el")
    (setq undercover-force-coverage t)
    (setenv "COVERALLS_REPO_TOKEN" "localrun")
    (undercover "*.el" (:report-file (expand-file-name "./coverage.json")) (:send-report nil))))

(require 'libgit2)
(require 'libgit2-magit)
