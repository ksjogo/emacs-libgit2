#include <git2.h>
#include <emacs-module.h>
#include <string.h>
#include <stdio.h>

/* Each function takes a single libgit2 type and converts it into an
 * emacs_value.  These conversions are shallow; do *not* optimize
 * these by flattening the vectors.  I have a feeling the consistency
 * will be
 well worth the verbosity.*/
extern emacs_value Fgit_status_t     (emacs_env *, const git_status_t *);
extern emacs_value Fgit_delta_t      (emacs_env *, const git_delta_t *);
extern emacs_value Fgit_diff_file    (emacs_env *, const git_diff_file *);
extern emacs_value Fgit_diff_delta   (emacs_env *, const git_diff_delta *);
extern emacs_value Fgit_status_entry (emacs_env *, const git_status_entry *);
extern emacs_value Fgit_oid          (emacs_env *, const git_oid *);
