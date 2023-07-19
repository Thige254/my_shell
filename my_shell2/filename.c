#include "shell.h"

/**
 * main - Entry point for the shell.
 * @argc: The number of arguments (including filename).
 * @argv: Array of arguments.
 *
 * Return: Always 0.
 */
int main(int argc, char **argv)
{
	if (argc == 2)
	{
		FILE *file = fopen(argv[1], "r");
		if (file == NULL)
		{
			perror("Error opening file");
			exit(EXIT_FAILURE);
		}

		char *line = NULL;
		size_t len = 0;
		ssize_t nread;

		while ((nread = getline(&line, &len, file)) != -1)
		{
			if (nread > 0 && line[nread - 1] == '\n')
				line[nread - 1] = '\0';

			if (*line != '\0' && *line != '#')
				execute_line(line);
		}

		free(line);
		fclose(file);
	}
	else if (argc == 1)
	{
		interactive_shell();
	}
	else
	{
		fprintf(stderr, "Usage: %s [filename]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	return (0);
}
