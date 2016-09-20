(ert-deftest libgit2/there-is-magic ()
  :tags '(general)
  (should (eq 42 (libgit2-magic))))
