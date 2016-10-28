#!/bin/sh
:;lldb -O'b Flibgit2_status' -o'r' -- emacs --script $0;exit $?
(add-to-list 'load-path ".")
(require 'libgit2)
(require 'pp)
(pp (libgit2-status))
