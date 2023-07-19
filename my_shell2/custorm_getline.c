#include "shell.h"

/**
 * custom_getline - Custom implementation of getline to read input.
 *
 * Return: A pointer to the input line.
 */
char *custom_getline(void)
{
	char *line = NULL;
	size_t bufsize = 0;
	ssize_t nread;

	nread = get_line(&line, &bufsize);
	if (nread == -1)
	{
		perror("read");
		exit(EXIT_FAILURE);
	}

	return (line);
}
