#include <git2.h>
#include <emacs-module.h>
#include <string.h>
#include <stdio.h>

/* Declare mandatory GPL symbol. */
int plugin_is_GPL_compatible;

/* Utils */

/* Bind NAME to FUN. */
static void bind_function (emacs_env *env, const char *name, emacs_value Sfun)
{
    /* Set the function cell of the symbol named NAME to SFUN using
       the 'fset' function. */

    /* Convert the strings to symbols by interning them */
    emacs_value Qfset = env->intern(env, "fset");
    emacs_value Qsym = env->intern(env, name);

    /* Prepare the arguments array */
    emacs_value args[] = { Qsym, Sfun };

    /* Make the call (2 == nb of arguments) */
    env->funcall(env, Qfset, 2, args);
}

/* Provide FEATURE to Emacs. */
static void provide (emacs_env *env, const char *feature)
{
    /* call 'provide' with FEATURE converted to a symbol */

    emacs_value Qfeat = env->intern(env, feature);
    emacs_value Qprovide = env->intern(env, "provide");
    emacs_value args[] = { Qfeat };

    env->funcall(env, Qprovide, 1, args);
}

/* For debugging purposes. */
static void message (emacs_env *env, const char *message)
{
    emacs_value Qmessage = env->intern(env, "message");
    emacs_value args[] = { env->make_string(env, message, strlen(message)) };
    env->funcall(env, Qmessage, 1, args);
}

/* For debugging purposes. */
static void pp (emacs_env *env, const char *fmt, emacs_value payload)
{
    emacs_value Qpp = env->intern(env, "pp-to-string");
    emacs_value args[] = { payload };
    emacs_value args2[] = { env->make_string(env, fmt, strlen(fmt)),
                            env->funcall(env, Qpp, 1, args) };
    env->funcall(env, env->intern(env, "message"), 2, args2);
}

/* Init */

static emacs_value Flibgit2_current_branch (emacs_env *env, ptrdiff_t nargs, emacs_value args[], void *data);
static emacs_value Flibgit2_status (emacs_env *env, ptrdiff_t nargs, emacs_value args[], void *data);

/* Initialize the module */
int emacs_module_init (struct emacs_runtime *ert)
{
    emacs_env *env = ert->get_environment(ert);
    git_libgit2_init();

#define DEFUN(lsym, csym, amin, amax, doc, data) \
    bind_function(env, lsym, env->make_function(env, amin, amax, csym, doc, data))

    DEFUN("libgit2-core-current-branch", Flibgit2_current_branch, 1, 1,
          "Return the current branch active of the repository at PATH."
          "\n\nSee also `libgit2-status'."
          "\n\n(fn PATH)", NULL);
    DEFUN("libgit2-core-status", Flibgit2_status, 1, 1,
          "Return the current status of the repository at PATH."
          "\n\nSee also `libgit2-status'."
          "\n\n(fn PATH)", NULL);

#undef DEFUN

    provide(env, "libgit2-core");

    return 0;
}

/* Implementation */

/* If you could alter CMakeLists in such a way that this isn't
 * necessary, I'd be eternally grateful :) */
#include "libgit2-core-convert-types.c"

static emacs_value Flibgit2_current_branch (emacs_env *env, ptrdiff_t nargs, emacs_value args[], void *data)
{
    /* args[0] := directory path */
    ptrdiff_t directory_size = 1000;
    char directory[directory_size];
    env->copy_string_contents(env, args[0], directory, &directory_size);

    const char *branch = NULL;

    git_repository *repo = NULL;
    git_repository_open_ext(&repo, directory, 0, NULL);

    if (repo != NULL) {
        git_reference *head = NULL;
        int error = git_repository_head(&head, repo);
        if (error == GIT_EUNBORNBRANCH || error == GIT_ENOTFOUND)
            branch = NULL;
        else if (!error) {
            branch = git_reference_shorthand(head);
        }
        git_reference_free(head);
    }

    if (branch == NULL)
        return env->intern(env, "no-branch");

    return env->make_string(env, branch, strlen(branch));
}

/* Retrieve the status of the repository.  Returns a plist or a hashmap -- something for fast access. */
/* Right now returns a vector. */
static emacs_value Flibgit2_status (emacs_env *env, ptrdiff_t nargs, emacs_value args[], void *data)
{
    /* args[0] := directory path for repository */
    ptrdiff_t directory_size = 1000;
    char directory[directory_size];
    env->copy_string_contents(env, args[0], directory, &directory_size);

    size_t status_i = 0;
    git_repository *repo = NULL;
    git_repository_open_ext(&repo, directory, 0, NULL);
    git_status_options opts = GIT_STATUS_OPTIONS_INIT;
    git_status_list *statuses = NULL;
    int error = git_status_list_new(&statuses, repo, &opts);

    size_t count = git_status_list_entrycount(statuses);
    if (count == 0) return NULL;

    emacs_value *status_values = malloc(sizeof(emacs_value) * count);
    emacs_value internal_status_values[3];
    for (status_i = 0; status_i < count; ++status_i) {
        const git_status_entry *entry = git_status_byindex(statuses, status_i);
        status_values[status_i] = Fgit_status_entry(env, git_status_byindex(statuses, status_i));
        pp(env, "this status value is %S", status_values[status_i]);
    }
    git_status_list_free(statuses);

    emacs_value Fvector = env->intern(env, "vector");
    emacs_value ret = env->funcall(env, Fvector, count, status_values);
    free(status_values);
    return ret;
}
