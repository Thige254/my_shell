#include "shell.h"

/**
 * split_commands - Splits the input line
 * into individual commands separated by ';'.
 * @line: The input line.
 *
 * Return: Array of strings containing individual commands.
 */
char **split_commands(char *line)
{
    if (line == NULL || *line == '\0')
        return NULL;

    int num_commands = count_commands(line);
    if (num_commands <= 0)
        return NULL;

    char **commands = malloc(sizeof(char *) * (num_commands + 1));
    if (commands == NULL)
        return NULL;

    int i;
    for (i = 0; i < num_commands; i++)
        commands[i] = get_next_command(&line);

    commands[i] = NULL;

    return commands;
}

/**
 * count_commands - Counts the number of
 * commands separated by ';'.
 * @line: The input line.
 *
 * Return: Number of commands.
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
 * get_next_command - Gets the next
 * command from the input line.
 * @line: The input line.
 *
 * Return: The next command.
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

/**
 * handle_commands_separator - Handles commands separated by ';'.
 * @line: The input line.
 *
 * Return: Status of the last command executed.
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
        if (status == EXIT_BUFFER_FLUSH)
            break;
    }

    free_array(commands);
    return status;
}

/**
 * execute_logical_operation - Executes the commands
 * with '&&' and '||' logical operators.
 * @line: The input line.
 *
 * Return: Status of the last command executed.
 */
int execute_logical_operation(char *line)
{
    char **commands = split_commands(line);
    int i, status = 0;
    int logical_op = 0; // 0 for '&&', 1 for '||'

    if (commands == NULL)
        return 0;

    for (i = 0; commands[i] != NULL; i++)
    {
        if (logical_op == 0)
        {
            // Execute the command with '&&' operator
            status = execute_command(commands[i]);
            if (status != 0)
            {
                // If a command fails, skip the rest with '&&'
                logical_op = 1;
            }
        }
        else
        {
            // Execute the command with '||' operator
            status = execute_command(commands[i]);
            if (status == 0)
            {
                // If a command succeeds, skip the rest with '||'
                logical_op = 0;
            }
        }

        if (status == EXIT_BUFFER_FLUSH)
            break;
    }

    free_array(commands);
    return status;
}
