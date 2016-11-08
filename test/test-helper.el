(add-to-list 'load-path default-directory)

(defun libgit2-gcov-collector ()
  (libgit2-core-dump-gcov)
  (message "%s" (shell-command-to-string "gcov -o CMakeFiles/git2-core.dir/ CMakeFiles/git2-core.dir/*.o"))
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

(defvar libgit2-testrepo (expand-file-name "./testrepo"))
(when (file-exists-p libgit2-testrepo)
  (delete-directory libgit2-testrepo t))
(make-directory libgit2-testrepo)

(let ((default-directory libgit2-testrepo))
  (shell-command-to-string "git init")
  (shell-command-to-string "git checkout -b testrepo")
  (shell-command-to-string "touch initial")
  (shell-command-to-string "git add initial")
  (shell-command-to-string "git commit -m 'initial'"))
