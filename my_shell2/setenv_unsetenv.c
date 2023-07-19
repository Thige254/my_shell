#include "shell.h"

/**
 * handle_setenv_builtin - Initialize a new environment variable
 *                        or modify an existing one.
 * @args: Array of arguments passed to the function.
 *        args[0] is the command "setenv"
 *        args[1] is the VARIABLE name
 *        args[2] is the VALUE to set
 *
 * Return: Always returns 0 (success).
 */
int handle_setenv_builtin(char **args)
{
	if (args[1] == NULL || args[2] == NULL)
	{
		fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
		return (1);
	}

	if (set_environment_variable(args[1], args[2]) == -1)
	{
		perror("handle_setenv_builtin");
		return (1);
	}

	return (0);
}

/**
 * handle_unsetenv_builtin - Remove an environment variable.
 * @args: Array of arguments passed to the function.
 *        args[0] is the command "unsetenv"
 *        args[1] is the VARIABLE name to unset
 *
 * Return: Always returns 0 (success).
 */
int handle_unsetenv_builtin(char **args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "Usage: unsetenv VARIABLE\n");
		return (1);
	}

	if (unset_environment_variable(args[1]) == -1)
	{
		perror("handle_unsetenv_builtin");
		return (1);
	}

	return (0);
}
