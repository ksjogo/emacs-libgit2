# emacs-libgit2

Emacs integration of the libgit2 library.
Requires `emacs-25` compiled after configured with `--with-modules`.

[![Build Status](https://travis-ci.org/ksjogo/emacs-libgit2.svg?branch=master)](https://travis-ci.org/ksjogo/emacs-libgit2)
[![Coverage Status](https://coveralls.io/repos/github/ksjogo/emacs-libgit2/badge.svg)](https://coveralls.io/github/ksjogo/emacs-libgit2)

## Building

``` shell
git submodule update --init --recursive
cmake .
make
```

## Emacs
This directory needs to be placed inside a folder which is in emacs load-path. Then `(require 'libgit2)` as usual.
