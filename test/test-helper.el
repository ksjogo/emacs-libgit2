(add-to-list 'load-path default-directory)

(when (require 'undercover nil t)
  (if (getenv "TRAVIS")
      (undercover "*.el")
    (message "undercover")
    (setq undercover-force-coverage t)
    (setenv "COVERALLS_REPO_TOKEN" "localrun")
    (undercover "*.el" (:report-file (expand-file-name "./coverage.json")) (:send-report nil))))

(require 'libgit2)
