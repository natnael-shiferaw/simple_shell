#include "shell.h"

/**
* main - USED TO CREATE A SIMPLE SHELL PROJECT
* @argc: REPRESENTS ARGUMENT COUNT
* @argv: REPRESENTS ARGUMENT VECTOR
*
* Return: 1 ON FAILURE. 0 ON SUCCESS.
*/

int main(int argc, char **argv)
{

	int X = 2;
	info_t INFORMATION[] = { {NULL, NULL, NULL, 0, 0, 0, 0, NULL,
	NULL, NULL, NULL, NULL, 0, 0, NULL, 0, 0, 0}};

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (X)
			: "r" (X));

	if (argc == 2)
	{
		X = open(argv[1], O_RDONLY);
		if (X == -1)
		{
			if (errno == EACCES)
				exit(126);

			if (errno == ENOENT)
			{
				_vputs(argv[0]);
				_vputs(": 0: Can't open ");
				_vputs(argv[1]);
				_vputchar('\n');
				_vputchar(-1);
				exit(127);
			}

			return (EXIT_FAILURE);
		}
		INFORMATION->read_nm = X;
	}

	env_population(INFORMATION);
	hist_read(INFORMATION);
	hsh(INFORMATION, argv);
	return (EXIT_SUCCESS);
}
