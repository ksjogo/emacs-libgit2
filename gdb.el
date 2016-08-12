(add-to-list 'load-path default-directory)
(require 'libgit2)
(libgit2-test)
(message (libgit2-status-branch))
