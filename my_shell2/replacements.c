#include "shell.h"

/**
 * replace_variable - Replaces special variables
 * like "$?" and "$$" with their values.
 * @args: The array of arguments (command and parameters).
 * @status: The exit status of the last command executed.
 * @pid: The process ID of the shell.
 */
void replace_variable(char **args, int status, int pid)
{
    char *dollar_sign = "$";
    char *question_mark = "?";
    char *pid_str = "$$";

    int i = 0;
    while (args[i])
    {
        if (strcmp(args[i], dollar_sign) == 0)
        {
            args[i] = get_env_value("?");
        }
        else if (strcmp(args[i], question_mark) == 0)
        {
            args[i] = convert_to_string(status);
        }
        else if (strstr(args[i], pid_str) != NULL)
        {
            char *pid_value = convert_to_string(pid);
            args[i] = replace_substring(args[i], pid_str, pid_value);
            free(pid_value);
        }
        i++;
    }
}

/**
 * get_env_value - Gets the value of an environment variable.
 * @name: The name of the environment variable.
 *
 * Return: The value of the environment variable, or NULL if not found.
 */
char *get_env_value(const char *name)
{
    return (getenv(name));
}

/**
 * convert_to_string - Converts an integer to a string.
 * @num: The integer to convert.
 *
 * Return: The converted string.
 */
char *convert_to_string(int num)
{
    int num_digits = count_digits(num);
    char *str = malloc((num_digits + 1) * sizeof(char));
    if (!str)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    sprintf(str, "%d", num);
    return str;
}

/**
 * count_digits - Counts the number of digits in an integer.
 * @num: The integer.
 *
 * Return: The number of digits.
 */
int count_digits(int num)
{
    int count = 0;
    if (num == 0)
    {
        return 1;
    }
    while (num != 0)
    {
        num /= 10;
        count++;
    }
    return count;
}

/**
 * replace_substring - Replaces all occurrences of a substring in a string.
 * @str: The original string.
 * @substr: The substring to replace.
 * @replacement: The replacement string.
 *
 * Return: The new string with the replacements.
 */
char *replace_substring(char *str, const char *substr, const char *replacement)
{
    if (!str || !substr || !replacement)
    {
        return NULL;
    }

    char *result = NULL;
    size_t i = 0;
    ssize_t j = 0; // Use ssize_t for j

    size_t len_str = strlen(str);
    size_t len_substr = strlen(substr);
    size_t len_replacement = strlen(replacement);

    result = (char *)malloc(len_str + 1);
    if (!result)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    while (i < len_str)
    {
        if (strstr(&str[i], substr) == &str[i])
        {
            for (size_t k = 0; k < len_replacement; k++)
            {
                result[j++] = replacement[k];
            }
            i += len_substr;
        }
        else
        {
            result[j++] = str[i++];
        }
    }

    result[j] = '\0';

    return result;
}
