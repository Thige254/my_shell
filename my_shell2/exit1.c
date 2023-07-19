#include "shell.h"

/**
 * my_exit - Exit the shell with the given status.
 * @info: Pointer to the shell information.
 *
 * Return: Always returns 0 (success).
 */
int my_exit(my_info_t *info)
{
	char **args = info->argv;
	int status = 0;

	if (args[1] != NULL)
	{
		status = atoi(args[1]);
	}

	free_shell_info(info, 1);

	exit(status);

	return (0);
}
