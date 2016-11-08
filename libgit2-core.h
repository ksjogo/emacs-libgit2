#ifndef LIBGIT2_CORE_H
#define LIBGIT2_CORE_H

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


#define PP_NARG(...)                            \
    PP_NARG_(__VA_ARGS__,PP_RSEQ_N())
#define PP_NARG_(...)                           \
    PP_ARG_N(__VA_ARGS__)
#define PP_ARG_N(                               \
    _1, _2, _3, _4, _5, _6, _7, _8, _9,_10,     \
    _11,_12,_13,_14,_15,_16,_17,_18,_19,_20,    \
    _21,_22,_23,_24,_25,_26,_27,_28,_29,_30,    \
    _31,_32,_33,_34,_35,_36,_37,_38,_39,_40,    \
    _41,_42,_43,_44,_45,_46,_47,_48,_49,_50,    \
    _51,_52,_53,_54,_55,_56,_57,_58,_59,_60,    \
    _61,_62,_63,  N, ...) N
#define PP_RSEQ_N()                             \
    63,62,61,60,                                \
        59,58,57,56,55,54,53,52,51,50,          \
        49,48,47,46,45,44,43,42,41,40,          \
        39,38,37,36,35,34,33,32,31,30,          \
        29,28,27,26,25,24,23,22,21,20,          \
        19,18,17,16,15,14,13,12,11,10,          \
        9, 8, 7, 6, 5, 4, 3, 2, 1, 0


#define INTERN(NAME) env->intern(env, NAME)
#define INTEGER(VALUE) env->make_integer(env, VALUE)
#define STRING(VALUE) env->make_string(env, VALUE, strlen(VALUE))
#define STRINGL(VALUE,LENGTH) env->make_string(env, VALUE, LENGTH)
#define NIL INTERN("nil")
#define VECTOR(name, ...)                                               \
    emacs_value name##_raw[] = {                                        \
        __VA_ARGS__                                                     \
    };                                                                  \
    emacs_value name = env->funcall(env, INTERN("vector"), PP_NARG(__VA_ARGS__), name##_raw);

#endif
