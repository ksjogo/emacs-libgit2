(add-to-list 'load-path default-directory)

(when (require 'undercover nil t)
  (undercover "*.el"))

(require 'libgit2)
