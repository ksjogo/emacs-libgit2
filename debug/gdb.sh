#!/bin/sh

if [ ! -f "libgit2-core.so" ]; then
    echo "please compile and start test/gdb.sh in repo root"
fi

if [ `hostname` = "guix" ]; then
    gdb --args `readlink -f ~/.guix-profile/bin/.emacs-26*real` -Q --load debug/gdb-entry.el
elif [ `hostname` = "ody.local" ]; then
    lldb -- /Applications/Emacs.app -Q --load debug/gdb-entry.el
fi
