#include "shell.h"

/**
* isCmd - USED TO DETERMINE IF THE COMMAND IS EXECUTABLE
* @stu: STRUCT PARAMETER
* @PATH: PATH
*
* Return: 1 ON SUCCESS, 0 ON FAILURE
*/

int isCmd(info_t *stu, char *PATH)
{
	struct stat ST;

	(void)stu;
	if (!PATH || stat(PATH, &ST))
		return (0);

	if (ST.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
* char_dup - USED FOR CHARACTER DUPLICATION
* @PATHstr: the string for THE PATH
* @initial: THE INITIAL INDEX
* @final: FINAL INDEX
*
* Return: POINTER TO THE NEW BUFFER.
*/

char *char_dup(char *PATHstr, int initial, int final)
{
	static char buf[1024];
	int j = 0, k = 0;

	for (k = 0, j = initial; j < final; j++)
		if (PATHstr[j] != ':')
			buf[k++] = PATHstr[j];
	buf[k] = 0;
	return (buf);
}

/**
* path_find - FINDS THE COMMAND IN THE PATH STRING
* @stu: THE STU STRUCT
* @PATHstr: THE PATH STRING
* @cmd: COMMAND TO FIND
*
* Return: PATH OF COMMAND, NULL OTHERWISE
*/

char *path_find(info_t *stu, char *PATHstr, char *cmd)
{
	char *PATH;
	int j = 0, poss_current = 0;

	if (!PATHstr)
		return (NULL);

	if ((_vstrlen(cmd) > 2) && vstarts_with(cmd, "./"))
	{
		if (isCmd(stu, cmd))
			return (cmd);
	}

	while (1)
	{
		if (!PATHstr[j] || PATHstr[j] == ':')
		{
			PATH = char_dup(PATHstr, poss_current, j);
			if (!*PATH)
				_vstrcat(PATH, cmd);
			else
			{
				_vstrcat(PATH, "/");
				_vstrcat(PATH, cmd);
			}
			if (isCmd(stu, PATH))
				return (PATH);
			if (!PATHstr[j])
				break;
			poss_current = j;
		}
		j++;
	}
	return (NULL);
}
