#include "shell.h"

/**
 * handle_exit_builtin - Handle the exit built-in, that exits the shell.
 * @args: The array of strings containing the command and its arguments.
 */
void handle_exit_builtin(char **args)
{
	(void)args;
	exit(EXIT_SUCCESS);
}
