#include "shell.h"

/**
 * handle_env_builtin - Print the current environment.
 *
 * Return: No return value.
 */
void handle_env_builtin(void)
{
	int i = 0;
	char *env_var;

	while (my_environ[i] != NULL)
	{
		env_var = my_environ[i];
		write(STDOUT_FILENO, env_var, strlen(env_var));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}
