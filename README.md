# emacs-libgit2

Emacs integration of the [libgit2][libgit2-home] library.
Requires `emacs-25` compiled after configured with `--with-modules`.

[![Build Status][travis-badge]][travis-link]
[![Coverage Status][coverage-badge]][coverage-link]
[![Chat][gitter-badge]][gitter-link]

## Status
Development setup is running. Only examplary git functions are integrated yet.

## Building
``` shell
git submodule update --init --recursive
cmake .
make
```

## Testing
Requires [cask][cask-home].
```shell
cask install
cmake -DCOVERAGE=ON .
make
cask exec ert-runner
```

## Emacs
This directory needs to be placed inside a folder which is in emacs
`load-path`, then `(require 'libgit2)` as usual.

[libgit2-home]: https://libgit2.github.com
[cask-home]: https://github.com/cask/cask
[travis-badge]: https://travis-ci.org/ksjogo/emacs-libgit2.svg?branch=master
[travis-link]: https://travis-ci.org/ksjogo/emacs-libgit2
[coverage-badge]: https://coveralls.io/repos/github/ksjogo/emacs-libgit2/badge.svg
[coverage-link]: https://coveralls.io/github/ksjogo/emacs-libgit2
[gitter-badge]:https://badges.gitter.im/emacs-libgit2/Lobby.svg
[gitter-link]:https://gitter.im/emacs-libgit2/Lobby
