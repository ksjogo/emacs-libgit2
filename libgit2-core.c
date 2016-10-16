#include <git2.h>
#include <emacs-module.h>
#include <string.h>

/* Declare mandatory GPL symbol.  */
int plugin_is_GPL_compatible;


/* UTILS */

/* Bind NAME to FUN.  */
static void bind_function (emacs_env *env, const char *name, emacs_value Sfun)
{
    /* Set the function cell of the symbol named NAME to SFUN using
       the 'fset' function.  */

    /* Convert the strings to symbols by interning them */
    emacs_value Qfset = env->intern(env, "fset");
    emacs_value Qsym = env->intern(env, name);

    /* Prepare the arguments array */
    emacs_value args[] = { Qsym, Sfun };

    /* Make the call (2 == nb of arguments) */
    env->funcall(env, Qfset, 2, args);
}

/* Provide FEATURE to Emacs.  */
static void provide (emacs_env *env, const char *feature)
{
    /* call 'provide' with FEATURE converted to a symbol */

    emacs_value Qfeat = env->intern(env, feature);
    emacs_value Qprovide = env->intern(env, "provide");
    emacs_value args[] = { Qfeat };

    env->funcall(env, Qprovide, 1, args);
}


/* FUNCS */

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


/* INIT */

int emacs_module_init (struct emacs_runtime *ert)
{
    emacs_env *env = ert->get_environment(ert);
    git_libgit2_init();

#define DEFUN(lsym, csym, amin, amax, doc, data) \
    bind_function(env, lsym, env->make_function(env, amin, amax, csym, doc, data))

    DEFUN("libgit2-core-current-branch", Flibgit2_current_branch, 1, 1,
          "Return the current branch active of PATH."
          "\n\nSee also `libgit2-status'."
          "\n\n(fn PATH)", NULL);

#undef DEFUN

    provide(env, "libgit2-core");

    return 0;
}
