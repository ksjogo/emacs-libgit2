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

(define-error 'libgit2-error "libgit2-error")

(defun libgit2-dir ()
  (expand-file-name default-directory))

(defun libgit2-get-current-branch ()
  (interactive)
  (libgit2-core-get-current-branch (libgit2-dir)))

;;;###autoload
(defun libgit2-status ()
  (interactive)
  (libgit2-core-status (libgit2-dir)))

(provide 'libgit2)
;;; libgit2.el ends here
