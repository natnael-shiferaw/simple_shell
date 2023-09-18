#include "shell.h"

/**
 * _vmemset - A FUNCTION THAT FILLS MEMORY WITH CONSTANT BYTE
 * @p: POINTER TO MEMORY AREA
 * @byte: THE BYTE TO FILL THE MEMORY AREA
 * @amount: AMOUNT OF BYTE TO BE FILLED
 * Return: RETURNS A POINTER TO MEMORY AREA
 */
char *_vmemset(char *p, char byte, unsigned int amount)
{
	unsigned int j;

	for (j = 0; j < amount; j++)
		p[j] = byte;
	return (p);
}

/**
 * vfree - A FUNCTION THAT FREES STRING OF STRINGS
 * @ss: REPRESENTS THE STRING OF STRINGS
 */
void vfree(char **ss)
{
	char **p = ss;

	if (!ss)
		return;
	while (*ss)
	    free(*ss++);
	free(p);
}

/**
 * _vrealloc - A FUCNTION THAT REALLOCATES BLOCK OF MEMORY
 * @PTR: REFERS TO THE PREVIOUS BLOCK THAT'S MALLOCATED
 * @PREV_size: PREVIOUS BLOCK BYTE SIZE
 * @newSIZE: NEW BLOCK BYTE SIZE
 *
 * Return: A POINTER TO THE PREVIOUS BLOCK NAME
 */

void *_vrealloc(void *PTR, unsigned int PREV_size, unsigned int newSIZE)
{
	char *p;

	if (!PTR)
		return (malloc(newSIZE));
	if (!newSIZE)
		return (free(PTR), NULL);
	if (newSIZE == PREV_size)
		return (PTR);

	p = malloc(newSIZE);
	if (!p)
		return (NULL);

	PREV_size = PREV_size < newSIZE ? PREV_size : newSIZE;
	while (PREV_size--)
		p[PREV_size] = ((char *)PTR)[PREV_size];
	free(PTR);
	return (p);
}
