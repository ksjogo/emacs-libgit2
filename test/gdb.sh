#!/bin/sh

if [ ! -f "libgit2-core.so" ]; then
    echo "please compile and start test/gdb.sh in repo root"
fi

if [ `hostname` = "guix" ]; then
    gdb --args emacs-25.2.50-real -Q --load test/gdb-entry.el
elif [ `hostname` = "ody.local" ]; then
    gdb --args emacs -Q --load test/gdb-entry.el
fi
