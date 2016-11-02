(add-to-list 'load-path default-directory)
(require 'libgit2)
(message (libgit2-status))
(ielm)
