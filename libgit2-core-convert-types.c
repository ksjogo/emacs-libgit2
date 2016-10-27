#include "libgit2-core.h"

emacs_value Fgit_status_t (emacs_env *env, const git_status_t *payload)
{
    return INTEGER(*payload);
}

emacs_value Fgit_delta_t (emacs_env *env, const git_delta_t *payload)
{
    switch (*payload) {
        case GIT_DELTA_UNMODIFIED: return INTERN("unmodified");
        case GIT_DELTA_ADDED: return INTERN("added");
        case GIT_DELTA_DELETED: return INTERN("deleted");
        case GIT_DELTA_MODIFIED: return INTERN("modified");
        case GIT_DELTA_RENAMED: return INTERN("renamed");
        case GIT_DELTA_COPIED: return INTERN("copied");
        case GIT_DELTA_IGNORED: return INTERN("ignored");
        case GIT_DELTA_UNTRACKED: return INTERN("untracked");
        case GIT_DELTA_TYPECHANGE: return INTERN("typechange");
        case GIT_DELTA_UNREADABLE: return INTERN("unreadable");
        case GIT_DELTA_CONFLICTED: return INTERN("conflicted");
    }
}

emacs_value Fgit_oid (emacs_env *env, const git_oid *payload)
{
    /* This is a special case.  Even though git_oid is a struct (and
     * thus should normally be cast as a vector), I'm confident it
     * exists only as a struct to hold a constant-size array of
     * values.  It should be safe to return these values as they
     * are. */
    return STRINGL(git_oid_tostr_s(payload), 40);
}

emacs_value Fgit_diff_file (emacs_env *env, const git_diff_file *payload)
{
    VECTOR(ret,
           INTERN("git-diff-file"),
           STRING(payload->path),
           INTEGER(payload->flags),
           INTEGER(payload->mode),
           Fgit_oid(env, &payload->id)
        );
    return ret;
}

emacs_value Fgit_diff_delta (emacs_env *env, const git_diff_delta *payload)
{
    /* new file?
     * we should probably report something, better than crashing though
     */
    if (payload == NULL) {
        VECTOR(ret,
               INTERN("git-diff-delta")
            );
        return ret;
    } else {
        VECTOR(ret,
               INTERN("git-diff-delta"),
               INTEGER(payload->flags),
               INTEGER(payload->nfiles),
               INTEGER(payload->similarity),
               Fgit_delta_t(env, &payload->status),
               Fgit_diff_file(env, &payload->old_file),
               Fgit_diff_file(env, &payload->new_file)
            );
        return ret;
    }
}

emacs_value Fgit_status_entry (emacs_env *env, const git_status_entry *payload)
{
    VECTOR(ret,
           INTERN("git-status-entry"),
           Fgit_status_t(env, &payload->status),
           Fgit_diff_delta(env, payload->index_to_workdir)
        );
    return ret;
}
