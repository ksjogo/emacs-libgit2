#include "libgit2-core.h"

emacs_value Fgit_status_t (emacs_env *env, const git_status_t *payload)
{
    return env->make_integer(env, *payload);
}

emacs_value Fgit_delta_t (emacs_env *env, const git_delta_t *payload)
{
    switch (*payload) {
    case GIT_DELTA_UNMODIFIED: return env->intern(env, "unmodified");
    case GIT_DELTA_ADDED:      return env->intern(env, "added");
    case GIT_DELTA_DELETED:    return env->intern(env, "deleted");
    case GIT_DELTA_MODIFIED:   return env->intern(env, "modified");
    case GIT_DELTA_RENAMED:    return env->intern(env, "renamed");
    case GIT_DELTA_COPIED:     return env->intern(env, "copied");
    case GIT_DELTA_IGNORED:    return env->intern(env, "ignored");
    case GIT_DELTA_UNTRACKED:  return env->intern(env, "untracked");
    case GIT_DELTA_TYPECHANGE: return env->intern(env, "typechange");
    case GIT_DELTA_UNREADABLE: return env->intern(env, "unreadable");
    case GIT_DELTA_CONFLICTED: return env->intern(env, "conflicted");
    }
}

emacs_value Fgit_oid (emacs_env *env, const git_oid *payload)
{
    char buf[41];
    for (int i = 0; i < 20; i++) {
        sprintf(buf + (i*2), "%02x", payload->id[i]);
    }
    /* This is a special case.  Even though git_oid is a struct (and
     * thus should normally be cast as a vector), I'm confident it
     * exists only as a struct to hold a constant-size array of
     * values.  It should be safe to return these values as they
     * are. */
    return env->make_string(env, buf, 40);
}

emacs_value Fgit_diff_file (emacs_env *env, const git_diff_file *payload)
{
    emacs_value Fvector = env->intern(env, "vector");
    emacs_value args[] = {
        env->intern(env, "git-diff-file"),
        env->make_string(env, payload->path, strlen(payload->path)),
        env->make_integer(env, payload->flags),
        env->make_integer(env, payload->mode),
        Fgit_oid(env, &payload->id)
    };
    return env->funcall(env, Fvector, 5, args);
}

emacs_value Fgit_diff_delta (emacs_env *env, const git_diff_delta *payload)
{
    emacs_value Fvector = env->intern(env, "vector");
    emacs_value args[] = {
        env->intern(env, "git-diff-delta"),
        env->make_integer(env, payload->flags),
        env->make_integer(env, payload->nfiles),
        env->make_integer(env, payload->similarity),
        Fgit_delta_t(env, &payload->status),
        Fgit_diff_file(env, &payload->old_file),
        Fgit_diff_file(env, &payload->new_file)
    };
    return env->funcall(env, Fvector, 7, args);
}

emacs_value Fgit_status_entry (emacs_env *env, const git_status_entry *payload)
{
    emacs_value args[] = {
        env->intern(env, "git-status-entry"),
        Fgit_status_t(env, &payload->status),
        Fgit_diff_delta(env, payload->index_to_workdir)
    };
    emacs_value Fvector = env->intern(env, "vector");
    return env->funcall(env, Fvector, 3, args);
}
