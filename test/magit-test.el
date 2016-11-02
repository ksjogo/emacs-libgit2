(require 'magit)
(ert-deftest libgit2/magit ()
  :tags '(general)
  (should (equal (libgit2-magit-get-current-branch) (magit-get-current-branch))))
