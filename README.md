# emacs-libgit2

[![Join the chat at https://gitter.im/emacs-libgit2/Lobby](https://badges.gitter.im/emacs-libgit2/Lobby.svg)](https://gitter.im/emacs-libgit2/Lobby?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

Emacs integration of the [libgit2][libgit2-home] library.
Requires `emacs-25` compiled after configured with `--with-modules`.

[![Build Status][travis-badge]][travis-link]
[![Coverage Status][coverage-badge]][coverage-link]

## Building

``` shell
git submodule update --init --recursive
cmake .
make
```

## Emacs
This directory needs to be placed inside a folder which is in emacs
`load-path`, then `(require 'libgit2)` as usual.

[libgit2-home]: https://libgit2.github.com
[travis-badge]: https://travis-ci.org/ksjogo/emacs-libgit2.svg?branch=master
[travis-link]: https://travis-ci.org/ksjogo/emacs-libgit2
[coverage-badge]: https://coveralls.io/repos/github/ksjogo/emacs-libgit2/badge.svg
[coverage-link]: https://coveralls.io/github/ksjogo/emacs-libgit2
