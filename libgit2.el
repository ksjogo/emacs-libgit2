;;; libgit2.el --- Emacs bindings for libgit2         -*- lexical-binding: t -*-

;; Copyright (c) 2016 Johannes Bernhard Goslar

;; Author: Johannes Bernhard Goslar
;; URL:
;; Keywords: git tools vc
;; Version: 0.1
;; Package-Requires: ((emacs "25"))

;;; Commentary:

;;; Code:
(require 'libgit2-core)

(defun libgit2-status ()
  (interactive)
  (libgit2-core-status (expand-file-name ".")))

(provide 'libgit2)
;;; libgit2.el ends here
