#ifndef _SHELL_H_
#define _SHELL_H_
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#define END_FILE -2
#define EXIT -3


extern char **environ;

char *name;

int hist_g;

/**
 * struct list_s - A new struct type defining a linked list.
 * @dir: A directory path.
 * @next_l: A pointer to another struct list_s.
 */
typedef struct list_s
{
	char *dir;
	struct list_s *next_l;
} list_t;

/**
 * struct builtin_s - A new struct type defining builtin commands.
 * @name: The name of the builtin command.
 * @f: A function pointer to the builtin command's function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(char **argv, char **front);
} builtin_t;

/**
 * struct alias_s - A new struct defining aliases.
 * @name: The name of the alias.
 * @value: The value of the alias.
 * @next_l: A pointer to another struct alias_s.
 */
typedef struct alias_s
{
	char *name;
	char *value;
	struct alias_s *next_l;
} alias_t;


alias_t *aliases;


ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_strtok(char *line, char *delim);
char *g_location(char *command);
list_t *g_path_dir(char *path);
int c_execute(char **args, char **front);
void list_free(list_t *head);
char *_itoa(int num);



int _strlen(const char *s);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);
char *_strcpy(char *dest, const char *src);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);


int (*g_builtin(char *command))(char **args, char **front);
int shel_exit(char **args, char **front);
int shel_env(char **args, char __attribute__((__unused__)) **front);
int shel_setenv(char **args, char __attribute__((__unused__)) **front);
int shel_unsetenv(char **args, char __attribute__((__unused__)) **front);
int shel_cd(char **args, char __attribute__((__unused__)) **front);
int shel_alias(char **args, char __attribute__((__unused__)) **front);
int shel_help(char **args, char __attribute__((__unused__)) **front);


void line_handle(char **line, ssize_t read);
void v_replace(char **args, int *exe_ret);
char *g_args(char *line, int *exe_ret);
int args_call(char **args, char **front, int *exe_ret);
int args_run(char **args, char **front, int *exe_ret);
int args_handle(int *exe_ret);
int args_check(char **args);
void args_free(char **args, char **front);
char **rep_aliases(char **args);


char **_copyenv(void);
void env_free(void);
char **_getenv(const char *var);


int creation_error(char **args, int err);
char *env_error(char **args);
char *error_1(char **args);
char *exit_error_2(char **args);
char *cd_error_2(char **args);
char *syntax_error_2(char **args);
char *error_126_h(char **args);
char *error_127_h(char **args);


alias_t *alias_add_end(alias_t **head, char *name, char *value);
void alias_list_free(alias_t *head);
list_t *node_add_end(list_t **head, char *dir);
void list_free(list_t *head);

void h_all(void);
void h_alias(void);
void h_cd(void);
void h_exit(void);
void h_help(void);
void h_env(void);
void h_setenv(void);
void h_unsetenv(void);
void h_history(void);

int file_process_commands(char *file_path, int *exe_ret);
#endif /* _SHELL_H_ */

