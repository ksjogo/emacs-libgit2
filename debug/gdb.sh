#!/bin/sh

if [ ! -f "libgit2-core.so" ]; then
    echo "please compile and start test/gdb.sh in repo root"
fi

if [ `hostname` = "guix" ]; then
    gdb --args `readlink -f ~/.guix-profile/bin/.emacs-26*real` -Q --load test/gdb-entry.el
elif [ `hostname` = "ody.local" ]; then
    gdb --args emacs -Q --load test/gdb-entry.el
fi
