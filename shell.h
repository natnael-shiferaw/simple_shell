#ifndef SHELL_H
#define SHELL_H

#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <limits.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

extern char **environ;

/**
* struct List_Str - Is a structure for singly linked list
* @Number: represents the number field
* @str: represents a string
* @next: a structure that points to the next node
*/

typedef struct List_Str
{
	int Number;
	char *str;
	struct List_Str *next;
} list_t;

/**
*struct inform_pass - pass arguments into a function,
*- Allows prototype for function pointer structure.
*@arg: IS a STRING coming FROM  getline.
*@argv: IS ARRAY of STRINGS FROM getline.
*@path: IS a path for a COMMAND THAT IS CURRENTLY IN USE.
*@argc: IT COUNTS ARRGUMENTS GIVEN IN TERMINAL.
*@error_count: IS the ERROR COUNT.
*@exit_err_num: IS THE CODE FOR error for exit() FUNCTION.
*@line_count_flag: line of INPUT IF ON COUNT
*@file_name: IS  PROGRAM filename
*@env_local: IS LOCAL COPY of environ
*@environ: MODIFIED COPY of environ from.
*@hist: REFERS TO THE HISTORY node
*@alias: REFERS TO the ALIAS node
*@env_updated: applys when environ is updated.
*@stat: IS RETURN STATUS of executed COMMAND LAST.
*@cmd_buffer: IS ADDRESS OF POINTER to cmd_buffer.
*@cmd_buffer_type: CMD_type ||, &&, ;
*@read_nm: USED to READ line input
*@hist_num_count: IS THE line Number count OF HISORY.
*/

typedef struct inform_pass
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int error_count;
	int exit_err_num;
	int line_count_flag;
	char *file_name;
	list_t *env_local;
	char **environ;
	list_t *hist;
	list_t *alias;
	int env_updated;
	int stat;

	char **cmd_buffer;
	int cmd_buffer_type;
	int read_nm;
	int hist_num_count;
} info_t;

/**
*struct built_in - STRUCT FOR BUILTIN STRING
*@flag: A FLAG.
*@function: A FUNCTION IN THIS STRUCTURE
*/

typedef struct built_in
{
	char *flag;
	int (*function)(info_t *);
} builtin_t;

/*line_gets.c */
void sign_handler(int);
int _getline(info_t *, char **, size_t *);
ssize_t read_buf(info_t *, char *, size_t *);
ssize_t buff_input(info_t *info, char **buf, size_t *len);
ssize_t retrieve_input(info_t *);

/* vexit.c */
char *_vstrncat(char *, char *, int);
char *_vstrchr(char *, char);
char *_vstrncpy(char *, char *, int);

/* errs.c */
int _putsnm(char *str, int nm);
int _vputchar(char);
void _vputs(char *);
int _putnm(char c, int nm);

/* errs_1.c */
void comments_removal(char *);
void error_display(info_t *, char *);
int d_print(int, int);
int _err_vatoi(char *);
char *number_conversion(long int, int, int);

/* _vstring.c */
int _vstrcmp(char *, char *);
char *_vstrcat(char *, char *);
char *vstarts_with(const char *, const char *);
int _vstrlen(char *);

/* _vstring1.c */
int _vputchar(char);
char *_vstrdup(const char *);
char *_vstrcpy(char *, char *);
void _vputs(char *);


/* TOKEN.c */
char **vstrtow1(char *, char);
char **vstrtow(char *, char *);

/* _vrealloc.c */
void *_vrealloc(void *, unsigned int, unsigned int);
void vfree(char **);
char *_vmemset(char *, char, unsigned int);


/*_vatoi.c */
int _vatoi(char *);
int _visalpha(int);
int inter_active(info_t *address);
int isDelim(char, char *);

/* memo.c */
int z_free(void **);

/* built_in.c */
int _help(info_t *);
int _cd(info_t *);
int _vexit(info_t *);

/* built_in_up.c */
int _alias(info_t *);
int _hist(info_t *);


/* PARSE.c */
char *path_find(info_t *, char *, char *);
char *char_dup(char *, int, int);
int isCmd(info_t *, char *);

/* info_get.c */
void info_set(info_t *, char **);
void info_free(info_t *, int);
void info_remove(info_t *);

/* VAR.c */
int var_replace(info_t *);
int isChain(info_t *, char *, size_t *);
int string_replace(char **, char *);
int alias_replace(info_t *);
void chain_check(info_t *, char *, size_t *, size_t, size_t);

/*environment.c */
int _setenv(info_t *);
int _env(info_t *);
char *_get_env(info_t *, const char *);
int env_population(info_t *);
int _unsetenv(info_t *);

/* get_environment.c */
int _setenv_(info_t *, char *, char *);
int _unsetenv_(info_t *, char *);
char **get_env(info_t *);


/* LIST.c */
void list_free(list_t **);
list_t *node_add_at_end(list_t **, const char *, int);
size_t Print_List_Str(const list_t *);
list_t *node_add(list_t **, const char *, int);
int remove_node_at_index(list_t **, unsigned int);

/* LIST_1.c */
list_t *node_begins_with(list_t *, char *, char);
size_t list_length(const list_t *);
ssize_t retrieve_node_at_index(list_t *, list_t *);
size_t list_print(const list_t *);
char **List_to_Strings(list_t *);

/*hist.c */
int hist_re_num(info_t *info);
int hist_read(info_t *info);
int hist_write(info_t *info);
char *get_hist_file(info_t *info);
int hist_list_build(info_t *info, char *buff, int linecount);

/* SHELL_LOOP.c */
int hsh_loop(char **);
int capture_builtin(info_t *);
void capture_cmd(info_t *);
int hsh(info_t *, char **);
void cmd_fork(info_t *);

#endif
