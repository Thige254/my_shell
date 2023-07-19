#include "shell.h"

/**
 * handle_alias_builtin - Handles the alias builtin command.
 * @args: The array of arguments (command and parameters).
 */
void handle_alias_builtin(char **args)
{
    if (args[1] == NULL)
        print_aliases(NULL);
    else if (args[2] == NULL)
        print_aliases(&args[1]);
    else
    {
        int i = 1;
        while (args[i])
        {
            add_alias(args[i], NULL);
            i++;
        }
    }
}

/**
 * add_alias - Adds an alias to the linked list.
 * @name: The name of the alias.
 * @value: The value of the alias.
 */
void add_alias(char *name, char *value)
{
    struct MyAlias *alias = malloc(sizeof(struct MyAlias));
    if (!alias)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    alias->name = strdup(name);
    if (!alias->name)
    {
        perror("strdup");
        free(alias);
        exit(EXIT_FAILURE);
    }

    if (value)
    {
        alias->value = strdup(value);
        if (!alias->value)
        {
            perror("strdup");
            free(alias->name);
            free(alias);
            exit(EXIT_FAILURE);
        }
    }
    else
        alias->value = NULL;

    alias->next = aliases;
    aliases = alias;
}

/**
 * print_aliases - Prints the aliases.
 * @names: An array of alias names to print (or NULL for all).
 */
void print_aliases(char **names)
{
    struct MyAlias *current = aliases;
    while (current)
    {
        if (names == NULL)
            printf("%s='%s'\n", current->name, current->value ? current->value : "");
        else
        {
            char **name_ptr = names;
            while (*name_ptr)
            {
                if (strcmp(*name_ptr, current->name) == 0)
                {
                    printf("%s='%s'\n", current->name, current->value ? current->value : "");
                    break;
                }
                name_ptr++;
            }
        }
        current = current->next;
    }
}
