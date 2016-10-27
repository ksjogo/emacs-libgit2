#!/usr/bin/env emacs --script
(require 'pp)
(add-to-list 'load-path (expand-file-name "."))
(require 'libgit2-core)

(pp (libgit2-core-status (expand-file-name ".")))
