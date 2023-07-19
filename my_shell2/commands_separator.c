#include "shell.h"

/**
 * handle_commands_separator - Handle the commands separated by ';'.
 * @line: The input line containing multiple commands.
 *
 * Return: Always returns 0 (success).
 */
int handle_commands_separator(char *line)
{
    char **commands = split_commands(line);
    int i, status = 0;

    if (commands == NULL)
        return 0;

    for (i = 0; commands[i] != NULL; i++)
    {
        status = execute_command(commands[i]);
        if (status == 1) // Use 1 instead of BUFFER_FLUSH if its value is 1
            break;
    }

    free_array(commands);
    return status;
}

/**
 * split_commands - Split the input line into individual commands.
 * @line: The input line containing multiple commands.
 *
 * Return: An array of strings where each element is a command.
 */
char **split_commands(char *line)
{
    char **commands;
    int i, num_commands;

    if (line == NULL || *line == '\0')
        return NULL;

    num_commands = count_commands(line);
    if (num_commands <= 0)
        return NULL;

    commands = malloc(sizeof(char *) * (num_commands + 1));
    if (commands == NULL)
        return NULL;

    for (i = 0; i < num_commands; i++)
        commands[i] = get_next_command(&line);

    commands[i] = NULL;

    return commands;
}

/**
 * count_commands - Count the number of commands in the input line.
 *
 * @line: The input line containing multiple commands.
 *
 * Return: The number of commands.
 */
int count_commands(char *line)
{
    int count = 0;
    int in_word = 0;

    while (*line)
    {
        if (*line == ';')
        {
            if (in_word)
                in_word = 0;
        }
        else if (!in_word)
        {
            in_word = 1;
            count++;
        }
        line++;
    }

    return count;
}

/**
 * get_next_command - Get the next command from the input line.
 * @line: The input line containing multiple commands.
 *
 * Return: A pointer to the next command.
 */
char *get_next_command(char **line)
{
    char *start = *line;

    while (**line && **line != ';')
        (*line)++;

    if (**line == '\0')
    {
        *line = NULL;
        return start;
    }

    *(*line)++ = '\0';

    return start;
}
