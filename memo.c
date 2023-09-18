#include "shell.h"

/**
* z_free - USED TO FREE A POINTER
* @PTR: ADDRESS OF THE POINTER TO BE FREED
*
* Return: 1 ON SUCCESS, 0 OTHERWISE.
*/

int z_free(void **PTR)
{
	if (PTR && *PTR)
	{
		free(*PTR);
		*PTR = NULL;
		return (1);
	}
	return (0);
}
