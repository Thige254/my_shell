#include "shell.h"
#include <string.h>

/**
 * handle_cd_home - Change the current directory to the HOME directory.
 *
 * Return: Always returns 0 (success).
 */
int handle_cd_home(void)
{
    char *home = get_env_value("HOME"); // Change get_environment_variable to get_env_value

    if (home == NULL)
    {
        fprintf(stderr, "cd: No home directory found.\n");
        return (1);
    }

    return (chdir(home));
}

/**
 * handle_cd_builtin - Change the current directory of the process.
 * @args: Array of arguments passed to the function.
 *        args[0] is the command "cd"
 *        args[1] is the optional DIRECTORY to change to
 *
 * Return: Always returns 0 (success).
 */
int handle_cd_builtin(char **args)
{
    char *prev_pwd = NULL;
    char *cur_pwd = NULL;

    if (args[1] == NULL)
        return (handle_cd_home());

    if (strcmp(args[1], "-") == 0)
    {
        prev_pwd = get_env_value("OLDPWD"); // Change get_environment_variable to get_env_value
        if (prev_pwd == NULL)
        {
            fprintf(stderr, "cd: OLDPWD not set.\n");
            return (1);
        }
        args[1] = prev_pwd;
    }

    cur_pwd = getcwd(NULL, 0);
    if (cur_pwd == NULL)
    {
        perror("cd");
        return (1);
    }

    if (chdir(args[1]) == -1)
    {
        perror("cd");
        free(cur_pwd);
        return (1);
    }

    set_environment_variable("OLDPWD", cur_pwd);
    set_environment_variable("PWD", getcwd(NULL, 0));
    free(cur_pwd);

    return (0);
}
