#include <emacs-module.h>
#include <git2.h>
#include <string.h>

/* Declare mandatory GPL symbol.  */
int plugin_is_GPL_compatible;

//UTILS

/* Bind NAME to FUN.  */
static void bind_function (emacs_env *env, const char *name, emacs_value Sfun)
{
  /* Set the function cell of the symbol named NAME to SFUN using
     the 'fset' function.  */

  /* Convert the strings to symbols by interning them */
  emacs_value Qfset = env->intern (env, "fset");
  emacs_value Qsym = env->intern (env, name);

  /* Prepare the arguments array */
  emacs_value args[] = { Qsym, Sfun };

  /* Make the call (2 == nb of arguments) */
  env->funcall (env, Qfset, 2, args);
}

/* Provide FEATURE to Emacs.  */
static void provide (emacs_env *env, const char *feature)
{
  /* call 'provide' with FEATURE converted to a symbol */

  emacs_value Qfeat = env->intern (env, feature);
  emacs_value Qprovide = env->intern (env, "provide");
  emacs_value args[] = { Qfeat };

  env->funcall (env, Qprovide, 1, args);
}

//FUNCS

static emacs_value Fmymod_test (emacs_env *env, ptrdiff_t nargs, emacs_value args[], void *data)
{
  git_libgit2_shutdown();
  return env->make_integer (env, 42);
}

static emacs_value Flibgit2_status (emacs_env *env, ptrdiff_t nargs, emacs_value args[], void *data)
{
  const char *branch = "abcde";
  git_repository *repo = NULL;
  git_status_list *status;
  git_status_options statusopt;
  statusopt.show  = GIT_STATUS_SHOW_INDEX_AND_WORKDIR;
  statusopt.flags = GIT_STATUS_OPT_INCLUDE_UNTRACKED |
    GIT_STATUS_OPT_RENAMES_HEAD_TO_INDEX |
    GIT_STATUS_OPT_SORT_CASE_SENSITIVELY;

  git_repository_open_ext(&repo, ".", 0, NULL);
  git_reference *head = NULL;
  int error = git_repository_head(&head, repo);
  if (error == GIT_EUNBORNBRANCH || error == GIT_ENOTFOUND)
    branch = NULL;
  else if (!error) {
    branch = git_reference_shorthand(head);
  }
  git_reference_free(head);
  return env->make_string(env,branch,strlen(branch));
}
//INIT

int emacs_module_init (struct emacs_runtime *ert)
{
  emacs_env *env = ert->get_environment (ert);
  git_libgit2_init();

#define DEFUN(lsym, csym, amin, amax, doc, data)  bind_function (env, lsym, env->make_function(env, amin, amax, csym, doc, data))

  DEFUN("libgit2-test", Fmymod_test, 0, 0, "libgit2 test", NULL);
  DEFUN("libgit2-status-branch", Flibgit2_status, 0, 0, "libgit2 status test return branch", NULL);

#undef DEFUN

  provide (env, "libgit2-core");

  return 0;
}
