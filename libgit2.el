(require 'libgit2-core nil t)

(defun libgit2-status ()
  (interactive)
  (libgit2-core-status (expand-file-name ".")))

(provide 'libgit2)
