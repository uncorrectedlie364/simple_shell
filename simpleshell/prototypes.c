#ifndef _shell_h
#define _shell_h

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/* Structure to hold environment variables in a linked list */

typedef struct liststr
{
	int num;	/* The number field */
	char *str;	/* A string */
	struct liststr *next;	/* Points to the next node */
} list_t;

/* Structure to hold pseudo-arguments for passing to functions */

typedef struct passinfo
{
	char *arg;	/* A string generated from getline containing args */
	char **argv;	/* An array of strings generated from arg */
	char *path;	/* A string path for the current command */
	int argc;	/* The argument count */
	unsigned int line_count;	/* The error count */
	int err_num;	/* The error code for exit() */
	int linecount_flag;	/* If on, count this line of input */
	char *fname;	/* The program filename */
	list_t *env;	/* Linked list local copy of environ */
	list_t *history;	/* The history node */
	list_t *alias;	/* The alias node */
	char **environ;	/* Custom modified copy of environ from LL env */
	int env_changed;	/* 1 if environ was changed */
	int status;	/* The return status of the last exec'd command */
	char **cmd_buf;	/* Address of pointer to cmd_buf, 1 if chaining */
	int cmd_buf_type;	/* CMD_type (||, &&, ;) */
	int readfd;	/* The fd from which to read line input */
	int histcount;	/* The history line number count */
} info_t;

/* Function prototypes */

int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);
int loophsh(char **);
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);
char **strtow(char *, char *);
char **strtow2(char *, char);
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);
int bfree(void **);
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);
int _myhistory(info_t *);
int _myalias(info_t *);
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif /*
