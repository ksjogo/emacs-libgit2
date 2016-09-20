# emacs-libgit2

Emacs integration of the libgit2 library.

[![Build Status](https://travis-ci.org/ksjogo/emacs-libgit2.svg?branch=master)](https://travis-ci.org/ksjogo/emacs-libgit2)

## Building

``` shell
git submodule update --init --recursive
cmake .
make
```

## Emacs Usage
                 This directory needs to be placed inside a folder which is in emacs load-path. Then `(require 'libgit2)` as usual.
