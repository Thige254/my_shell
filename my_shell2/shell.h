#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

/**
 * struct MyAlias - Structure to represent an alias in the shell.
 * @name: The name of the alias.
 * @value: The value of the alias.
 * @next: Pointer to the next alias in the linked list.
 */
struct MyAlias
{
    char *name;
    char *value;
    struct MyAlias *next;
};

/* Global variable for aliases */
extern struct MyAlias *aliases;
extern char **my_environ;

/* Main shell functions */
void interactive_shell(void);
int execute_line(char *line);
char **split_input(char *line);
int execute_command(char *command);

/* Built-in functions */
void handle_cd(char **args);
void handle_exit(char **args);
void handle_env(char **args);
void handle_alias_builtin(char **args);
int handle_setenv_builtin(char **args);
int handle_unsetenv_builtin(char **args);

/* Utility functions */
char **split_commands(char *line);
int count_commands(char *line);
char *get_next_command(char **line);
int handle_commands_separator(char *line);
int execute_logical_operation(char *line);
void replace_variable(char **args, int status, int pid);
char *get_env_value(const char *name);
char *convert_to_string(int num);
int count_digits(int num);
char *replace_substring(char *str, const char *substr, const char *replacement);
void free_array(char **array);

/* Batch mode function */
int main(int argc, char **argv);

/* Function prototypes for added functions */
void execute_shell(const char *filename);
void execute_interactive(void);
void print_aliases(char **names);
void add_alias(char *name, char *value);

/* Path handling functions */
char *find_command_path(const char *dir, const char *command);
char *string_concatenate(const char *str1, const char *str2);
void print_error_message(const char *command);

/* Environment variable functions */
int set_environment_variable(const char *name, const char *value);
int unset_environment_variable(const char *name);

/* Exit status for buffer flush */
#define EXIT_BUFFER_FLUSH 10

#endif /* SHELL_H */
