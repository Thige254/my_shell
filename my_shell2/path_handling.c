#include "shell.h"

/**
 * handle_path - Handle the PATH and execute the command.
 * @args: The array of strings containing the command and its arguments.
 */
void handle_path(char **args)
{
    char *command_path;
    char *full_command = NULL;
    char *path = getenv("PATH");
    char **directories = split_input(path);
    int i;

    for (i = 0; directories && directories[i]; i++)
    {
        command_path = find_command_path(directories[i], args[0]);
        if (command_path)
        {
            char *path_with_slash = string_concatenate(command_path, "/");
            full_command = string_concatenate(path_with_slash, args[0]);
            free(command_path);
            free(path_with_slash);
            break;
        }
    }

    if (!directories || !directories[i])
    {
        print_error_message(args[0]);
        free_array(directories);
        return;
    }

    free_array(directories);

    if (full_command)
    {
        execute_command(full_command); // Pass the full_command directly
        free(full_command);
    }
    else
    {
        printf("Command not found: %s\n", args[0]);
    }
}
