#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

#define MAX_ARGS 64
#define ARG_DELIMITER " \t\n"

struct MyAlias
{
    char *name;
    char *value;
    struct MyAlias *next;
};

struct MyAlias *aliases;
char **my_environ;

char *custom_getline(void)
{
    char *line = NULL;
    size_t bufsize = 0; // Let getline handle dynamic memory allocation

    if (getline(&line, &bufsize, stdin) == -1)
    {
        if (feof(stdin))
        {
            printf("\n");
            exit(EXIT_SUCCESS);
        }
        else
        {
            perror("custom_getline: getline error");
            exit(EXIT_FAILURE);
        }
    }

    // Remove the newline character if it exists
    size_t len = strlen(line);
    if (len > 0 && line[len - 1] == '\n')
        line[len - 1] = '\0';

    return line;
}

char **split_input(char *line)
{
    char **tokens = NULL;
    int bufsize = MAX_ARGS;
    int position = 0;
    char *token;

    tokens = malloc(bufsize * sizeof(char *));
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
    return tokens;
}

int execute_command(char *command)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == -1)
    {
        perror("execute_command: fork error");
        return EXIT_FAILURE;
    }
    if (pid == 0)
    {
        /* Child process */
        if (execlp(command, command, NULL) == -1)
        {
            perror("execute_command: execution error");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        /* Parent process */
        do
        {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return status;
}

void interactive_shell(void)
{
    char *line;
    char **args;
    int status;

    while (1)
    {
        printf("$ ");
        line = custom_getline();
        if (!line)
            break;

        args = split_input(line);
        free(line);

        if (!args || !args[0])
        {
            free(args);
            continue;
        }

        status = execute_command(args[0]);
        free(args);
        if (status == EXIT_SUCCESS)
            break;
    }
}

int main(void)
{
    interactive_shell();
    return EXIT_SUCCESS;
}
