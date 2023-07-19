#include "shell.h" // Include shell.h to access the constants and function prototypes

#define MAX_ARGS 64 // Add the MAX_ARGS constant
#define ARG_DELIMITER " \t\n" // Add the ARG_DELIMITER constant

/**
 * split_input - Split the input line into individual commands and arguments.
 * @line: The input line to split.
 *
 * Return: An array of strings containing the commands and arguments.
 */
char **split_input(char *line)
{
    int bufsize = MAX_ARGS;
    int position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;

    if (!tokens)
    {
        perror("split_input: allocation error");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, ARG_DELIMITER);
    while (token != NULL)
    {
        tokens[position] = token;
        position++;

        if (position >= bufsize)
        {
            bufsize += MAX_ARGS;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens)
            {
                perror("split_input: reallocation error");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, ARG_DELIMITER);
    }
    tokens[position] = NULL;
    return (tokens);
}

/**
 * execute_command - Execute the command and return its exit status.
 * @command: The command to be executed.
 *
 * Return: The exit status of the command.
 */
int execute_command(char *command)
{
    char *line = strdup(command); // Copy the command to avoid modifying the original string
    int status = execute_line(line);
    free(line);
    return status;
}
