(ert-deftest libgit2/status ()
  :tags '(general)
  (let ((default-directory libgit2-testrepo))
    (shell-command-to-string "touch testfile")
    (shell-command-to-string "git add testfile")
    (should (vectorp (libgit2-status)))))

(ert-deftest libgit2/branch ()
  :tags '(general)
  (let ((default-directory libgit2-testrepo))
    (should (string-equal "testrepo" (libgit2-get-current-branch)))))

(ert-deftest libgit2/signal-error ()
  :tags '(general error)
  (let ((default-directory libgit2-testrepo))
    (should-error (libgit2-core-get-current-branch "") :type 'libgit2-error)))
