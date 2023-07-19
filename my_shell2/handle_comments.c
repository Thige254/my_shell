#include "shell.h"

/**
 * handle_comments - Removes comments from the input line.
 * @line: The input line.
 */
void handle_comments(char *line)

{
	char *hash_symbol = "#";
	char *comment_start = strstr(line, hash_symbol);
	if (comment_start)
		*comment_start = '\0';
}
