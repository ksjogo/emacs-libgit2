;;; libgit2.el --- Emacs bindings for libgit2         -*- lexical-binding: t -*-

;; Copyright (c) 2016 Johannes Goslar

;; Author: Johannes Goslar
;; URL: https://github.com/ksjogo/emacs-libgit2
;; Keywords: git tools vc
;; Version: 0.1
;; Package-Requires: ((emacs "25"))

;;; Commentary:

;;; Code:
(unless (require 'libgit2-core nil t)
  (message "could not load compiled libgit2-core module!"))

(defun libgit2-status ()
  (interactive)
  (libgit2-core-current-branch (expand-file-name ".")))

(provide 'libgit2)
;;; libgit2.el ends here
