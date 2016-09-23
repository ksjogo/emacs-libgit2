#!/bin/sh

if [ ! -f "libgit2-core.so" ]; then
    echo "please compile and start test/gdb.sh in repo root"
fi

if [ `hostname` = "guix" ]; then
    gdb --args .emacs-25.2.50-real  -Q --load test/gdb-entry.el
else
    echo "unknown hostname, add your gdb setup here"
fi
