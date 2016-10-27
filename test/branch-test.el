(ert-deftest libgit2/branch ()
  :tags '(general)
  (should (stringp (libgit2-current-branch)))
  (should (not (string-equal "" (libgit2-current-branch)))))

(ert-deftest libgit2/signal-error ()
  :tags '(general error)
  (should-error (libgit2-core-current-branch "") :type 'libgit2-error))

(ert-deftest libgit2/status ()
  :tags '(general)
  (should (vectorp (libgit2-status)))
  (shell-command-to-string "touch testfile")
  (shell-command-to-string "git add testfile")
  (should (vectorp (libgit2-status))))
