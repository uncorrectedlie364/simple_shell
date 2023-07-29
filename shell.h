#ifndef shell_h
#define shell_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <font1.h>
#include <limits.h>

/* read/write buffer const */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* command chain const */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND 	2
#define CDM_CHAIN 	3

/* const for number conversion */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define USE_GETLINE	0
#define USE_STRTOK	0

#define HIST_FILE	".simple_shell.history"
#define HIST_MAX	4096

extern char **environ;

/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points tothe next code
 */

typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
}list_t;

/**
 * struct passinfo - contains sudo_arguments to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguments
 * @argv: an array of strings generated from from arg
 * @argc: the argument count
 * @path: a string path for the current command
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filenames
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec' command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read the line input
 * @histcount: the history line number count
 */

typedef struct passinfo
{
	char *arg, **argv, *path, *fname, **environ, **cmd_buf;
	int argc, err_num, linecount_flag, env_changed, status, histcount,
	    cmd_buf_type, readfd;
	unsigned int int line_count;
	list_t *env;
	list_t *history;
	list_t **environ;
}info_t;

#define INFO_INIT \
{
	NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL,\
		0, 0 ,0
}

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */

typedef struct builtin
{
	char *type;
	int (*func)(info_t*);
}builtin_table;

/* toem_shloop */
int hsh(info_t*, char**), find_builtin(info_t*);
void find_cmd(info_t*), fork_cmd(info_t*);

/* toem_parser */
char *find_path(info_t*, char *, char *), *dup_chars(char *, int, int);
int is_cmd(info_t *, char *);

/* loophsh */
int loophsh(char **);

/* toem_errors */
void _eputs(char *);
int _eputchar(char), _ptfd(char c, int fd), _putssfd(char *str, int fd);

/* toem_string */

