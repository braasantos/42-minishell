#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdbool.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../includes/LIBFT/libft.h"

extern int g_signal;

typedef enum e_op
{
	COMMAND_NOT_FOUND,
} t_op;

typedef struct s_mini
{
	char *path_to_cmd; // for execve
	char **exec_args;  // for execve
	char **newenvp;
	char **args;	 // all the args
	char **new_args; // args splitted without the pipes
	pid_t *newpro;
	char *new_str;
	int *pipes_fd;
	int fd1;
	int fd0;
	int STDIN;
	int STDOUT;
	int exit_flag;
} t_mini;

/* ************************************************************************** */
/*			                    builtins	                   				   */
/* ************************************************************************** */
int str_len(char **str);
int have_redirect(t_mini *mini);
int builtins(t_mini *mini);
int find_env_var(char *var, t_mini *mini);
char **realloc_envv(int new_size, t_mini *mini);
void set_env_var(char *key, char *value, t_mini *mini);
int ft_strendswith(char *s1, char *s2);
char *ft_pathjoin(char *p1, char *p2);
char *get_env(char *var, t_mini *mini);
void change_dir(char *path, t_mini *mini);
int get_cd(t_mini *mini);
int ft_strstartswith(char *s1, char *s2);
int echo_cmd(char **tokens);
int ft_check_echo_arguments(char *array_args);
void ft_print_echo_space(char **aux);
void ft_print_new_line(int flag_nl);

/* ************************************************************************** */
/*				execution					   */
/* ************************************************************************** */
void execute(t_mini *mini);
void first_pipe(t_mini *mini, char *s);
void second_pipe(t_mini *mini);
void create_flow(t_mini *mini);

/* ************************************************************************** */
/*				parser.c					   */
/* ************************************************************************** */

bool is_a_option(char *s, t_mini *mini);
bool is_a_file(char *s);
bool is_a_cmd(char *s, t_mini *mini);
bool is_a_red(char *s);
bool is_a_pipe(char *s);
char **split_to_split(t_mini *mini, char *s);
void create_file(t_mini *mini);
bool is_a_file_to_create(char *s, t_mini *mini);
void update_path(t_mini *mini, int i);
void delete_path(t_mini *mini);
void pad(char *src, char *dest, int i, int j);
int find_char(char c, char *find);
int padding_needed(char *str, int i, int pad);
char *pad_central(char *str);
int quotes_open(char *str, int target_index);
int pipe_check(char *str);
int redirect_basic_check(char *str);
int ft_check_open_quotes(char *str);
int count_pipes(t_mini *mini);
void print(t_op op, char *ag);
int check_args(char *str);
int ft_strcmp(char *str1, char *str2);
char **get_newenvp(char **envp);
char **get_path(char **newenv);
char *ft_add(t_mini *mini, char *ag);
void ft_free_arr(char **str);

/* ************************************************************************** */
/*				parser.c					   */
/* ************************************************************************** */
void create_child(t_mini *mini, int i, int flag, int j);
void parsing(t_mini *mini, char *str);
void ft_exit(t_mini *mini);

/* ************************************************************************** */
/*				                 pipes                              	      */
/* ************************************************************************** */

void ft_child2(t_mini *mini);
void ft_child1(t_mini *mini, char *s);
void firs_pipe(t_mini *mini, char *s);
void second_c(t_mini *mini, int j, int count, char *s);
void close_final(t_mini *mini);
void middle_pipe(t_mini *mini);

/* ************************************************************************** */
/*				checker					   */
/* ************************************************************************** */
int check_position(t_mini *mini, int j);
/* ************************************************************************** */
/*				                      signal	             				  */
/* ************************************************************************** */
void ft_init_signals(void);
void ft_ignore_signals(void);
void ft_restore_signals(void);
void ft_handle_eof(void);
void ft_handle_sigint(int sig);
void ft_handle_sigint_ign(int sig);
void ft_handle_sigquit(int sig);
/* ************************************************************************** */
/*				parser.c					   */
/* ************************************************************************** */

int isPipeOpen(int fd);
int isPipeOpenForWriting(int fd);
int check_position_bool(t_mini *mini, char *to_find);
void for_loop(char **s);
void through_pipes(t_mini *mini, int i);
void close_pipes(t_mini *mini);
void get_exit_status(t_mini *mini);
#endif
