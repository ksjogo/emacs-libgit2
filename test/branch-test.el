(ert-deftest libgit2/branch ()
  :tags '(general)
  (should (stringp (libgit2-current-branch)))
  (should (not (string-equal "" (libgit2-current-branch))))
  (should (eq 'need-path (libgit2-core-current-branch ""))))

(ert-deftest libgit2/status ()
  :tags '(general)
  (should (or (vectorp (libgit2-status)) (not (libgit2-status)))))
