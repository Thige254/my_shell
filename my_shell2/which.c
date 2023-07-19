#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH_LENGTH 1024
#define MAX_FILENAME_LENGTH 256

/**
 * file_exists_in_dir - Check if a file exists in the given directory.
 * @filename: The name of the file to check.
 * @directory: The directory to search for the file in.
 *
 * Return: 1 if the file is found, 0 otherwise.
 */
int file_exists_in_dir(const char *filename, const char *directory)
{
	char filepath[MAX_PATH_LENGTH];
	snprintf(filepath, sizeof(filepath), "%s/%s", directory, filename);
	
	FILE *file = fopen(filepath, "r");
	if (file)
	{
		fclose(file);
		return (1);
	}
	return (0);
}

/**
 * main - Entry point of the program.
 * @argc: The number of arguments passed to the program.
 * @argv: An array of strings containing the arguments.
 *
 * Return: Always 0.
 */
int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("Usage: %s filename ...\n", argv[0]);
		return (1);
	}

	char *path = getenv("PATH");

	if (path == NULL)
	{
		printf("No PATH environment variable found.\n");
		return (1);
	}

	char *token = strtok(path, ":");
	while (token != NULL)
	{
		for (int i = 1; i < argc; i++)
		{
			if (file_exists_in_dir(argv[i], token))
			{
				printf("%s/%s\n", token, argv[i]);
			}
		}
		token = strtok(NULL, ":");
	}

	return (0);
}

