#include "shell.h"

int main(int argc, char *argv[])
{
	if (argc == 2)
	{
		execute_shell(argv[1]);
	}
	else
	{
		execute_interactive();
	}

	return 0;
}
