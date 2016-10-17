(ert-deftest libgit2/linked ()
  :tags '(general)
  (should (fboundp #'libgit2-core-status)))
