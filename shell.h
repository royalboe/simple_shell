#ifndef _SHELL_H_
#define _SHELL_H_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdarg.h>
#include <signal.h>



/**
 * struct builtin_d - Defines the builtins functions.
 * @built: The name of the build in command.
 * @f: A pointer to the right builtin function.
 */
typedef struct builtin_d
{
	char *built;
	void (*f)(char *);
} builtin_t;

extern char **environ;

char **get_root(char *, const char *, int);
int count_parts(char *, const char *);
char **split(int, char *, const char *);
void create_child(char **, char *, int, char **);
void parse_line(char *, size_t, int, char **);
char *path_finder(char *);
int _strlen(char *);
int find_path(char *);
char **split_path(int, char *);
char *search_dir(char **, char *);
char *build_path(char *, char *);
void _free2(char **);
void _free(int, ...);
int find_the_way(char *dir, char *comand);
char *join_path(int len, char *dir, char *comm);
int builtin(char **, char *);
void (*check_built_ins(char *))(char *);
void exit_cmd(char *);
void env_cmd(char *);

/*string functions*/
int _strcmp(char *, char *);
char *_strdup(char *);
void print_str(char *, int);
int print_number(int);
int _write_char(char);

/* Helper functions*/
void printing_err(char *, int, char *);
void exec_err(char *, int, char *);

#endif
