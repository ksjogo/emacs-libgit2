(add-to-list 'load-path default-directory)

(ert-deftest libgit2/there-is-magic ()
  :tags '(general)
  (require 'libgit2)
  (should (eq 42 (libgit2-magic))))
