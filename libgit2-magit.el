;;; libgit2-magit.el --- Magit alias for libgit2-core         -*- lexical-binding: t -*-
;;; Commentary:
;; Currently we are defining alias, so we do not have to do development on multiple branches

;;; Code:
(require 'libgit2)

;;;###autoload
(defun libgit2-enable-magit-alias ()
  (defalias 'magit-get-current-branch 'libgit2-get-current-branch))

(provide 'libgit2-magit)
;;; libgit2.el ends here
