(ert-deftest libgit2/status ()
  :tags '(general)
  (message (libgit2-status))
  (should (not (string-equal "" (libgit2-status)))))
