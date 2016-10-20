#include "libgit2-core.h"

/* Declare mandatory GPL symbol. */
int plugin_is_GPL_compatible;

/* Utils */

/* Bind NAME to FUN. */
void bind_function (emacs_env *env, const char *name, emacs_value Sfun)
{
    /* Set the function cell of the symbol named NAME to SFUN using
       the 'fset' function. */

    /* Convert the strings to symbols by interning them */
    emacs_value Qfset = INTERN("fset");
    emacs_value Qsym = INTERN(name);

    /* Prepare the arguments array */
    emacs_value args[] = { Qsym, Sfun };

    /* Make the call (2 == nb of arguments) */
    env->funcall(env, Qfset, 2, args);
}

/* Provide FEATURE to Emacs. */
void provide (emacs_env *env, const char *feature)
{
    /* call 'provide' with FEATURE converted to a symbol */

    emacs_value Qfeat = INTERN(feature);
    emacs_value Qprovide = INTERN("provide");
    emacs_value args[] = { Qfeat };

    env->funcall(env, Qprovide, 1, args);
}

/* For debugging purposes. */
void message (emacs_env *env, const char *message)
{
    emacs_value Qmessage = INTERN("message");
    emacs_value args[] = { STRING(message) };
    env->funcall(env, Qmessage, 1, args);
}

/* For debugging purposes. */
void pp (emacs_env *env, const char *fmt, emacs_value payload)
{
    emacs_value Qpp = INTERN("pp-to-string");
    emacs_value args[] = { payload };
    emacs_value args2[] = { STRING(fmt), env->funcall(env, Qpp, 1, args) };
    env->funcall(env, INTERN("message"), 2, args2);
}

/* Init */

emacs_value Flibgit2_current_branch (emacs_env *env, ptrdiff_t nargs, emacs_value args[], void *data);
emacs_value Flibgit2_status (emacs_env *env, ptrdiff_t nargs, emacs_value args[], void *data);

/* Initialize the module */
int emacs_module_init (struct emacs_runtime *ert)
{
    emacs_env *env = ert->get_environment(ert);
    git_libgit2_init();

#define DEFUN(lsym, csym, amin, amax, doc, data)                        \
    bind_function(env, lsym, env->make_function(env, amin, amax, csym, doc, data))

    DEFUN("libgit2-core-current-branch", Flibgit2_current_branch, 1, 1,
          "Return the current branch active of the repository at PATH."
          "\n\nSee also `libgit2-current-branch'."
          "\n\n(fn PATH)", NULL);
    DEFUN("libgit2-core-status", Flibgit2_status, 1, 1,
          "Return the current status of the repository at PATH."
          "\n\nSee also `libgit2-status'."
          "\n\n(fn PATH)", NULL);

#undef DEFUN

    provide(env, "libgit2-core");

    return 0;
}

#define CHECK_REPOSITORY(NAME) /* args[0] := directory path for repository */ \
    ptrdiff_t directory_size = 1000;\
    char directory[directory_size];\
    env->copy_string_contents(env, args[0], directory, &directory_size);\
    if (strlen(directory) == 0)\
        return INTERN("need-path");\
    git_repository *NAME = NULL;\
    git_repository_open(&NAME, directory);\
    if (NAME == NULL)\
        return INTERN("not-a-repository");\

/* Implementation */

emacs_value Flibgit2_current_branch (emacs_env *env, ptrdiff_t nargs, emacs_value args[], void *data)
{
    CHECK_REPOSITORY(repo);

    const char *branch = NULL;
    git_reference *head = NULL;

    int error = git_repository_head(&head, repo);
    if (error == GIT_EUNBORNBRANCH || error == GIT_ENOTFOUND)
        branch = NULL;
    else if (!error)
        branch = git_reference_shorthand(head);

    git_reference_free(head);

    if (branch == NULL)
        return INTERN("no-branch");

    return STRING(branch);
}

/* Retrieve the status of the repository.  Returns a plist or a hashmap -- something for fast access. */
/* Right now returns a vector. */
emacs_value Flibgit2_status (emacs_env *env, ptrdiff_t nargs, emacs_value args[], void *data)
{
    CHECK_REPOSITORY(repo);

    git_status_options opts = GIT_STATUS_OPTIONS_INIT;
    git_status_list *statuses = NULL;
    int error = git_status_list_new(&statuses, repo, &opts);

    size_t count = git_status_list_entrycount(statuses);
    if (count == 0)
        return NULL;

    emacs_value *status_values = malloc(sizeof(emacs_value) * count);
    emacs_value internal_status_values[3];
    for (size_t status_i = 0; status_i < count; ++status_i) {
        const git_status_entry *entry = git_status_byindex(statuses, status_i);
        status_values[status_i] = Fgit_status_entry(env, git_status_byindex(statuses, status_i));
    }
    git_status_list_free(statuses);

    emacs_value Fvector = INTERN("vector");
    emacs_value ret = env->funcall(env, Fvector, count, status_values);
    free(status_values);
    return ret;
}
