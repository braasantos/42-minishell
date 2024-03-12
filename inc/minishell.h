#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/stat.h>
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
	char **newenvp;	   // the copy of the env variable
	char **args;	   // the new_str splitted
	pid_t *newpro;	   // for fork
	char *str;		   // str with the initial string
	char *new_str;	   // worked string
	int *pipes_fd;	   // for pipes
	int fd1;
	int fd0;
	int STDIN;
	int STDOUT;
	int stdin_fd;
	int stdout_fd;
	int flag;
	int echo_flag;
	int exit_flag;
	char *before;
	char *after;
	bool pipe_or_redirect_found;
	bool	interact;
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
int echo_cmd(char **tokens, t_mini *mini);
int ft_check_echo_arguments(char *array_args);
void ft_print_new_line(int flag_nl);

/* ************************************************************************** */
/*				execution					   */
/* ************************************************************************** */
void execute(t_mini *mini);
void create_flow(t_mini *mini);

/* ************************************************************************** */
/*				parser.c					   */
/* ************************************************************************** */

bool is_a_option(char *s, t_mini *mini);
bool is_a_file(char *s);
bool is_a_cmd(char *s, t_mini *mini);
bool is_a_red(char *s);
bool is_a_pipe(char *s);
char **split_to_split(t_mini *mini, int i);
void create_file(t_mini *mini);
bool is_a_file_to_create(char *s, t_mini *mini);
void update_path(t_mini *mini, int i);
void delete_path(t_mini *mini);
void pad(char *src, char *dest, int i, int j);
int find_char(char c, char *find);
int padding_needed(char *str, int i, int pad);
char *pad_central(char *str);
int quotes_open(char *str, int target_index);
int pipe_check(t_mini *mini, char *str);
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
int create_child(t_mini *mini, int i, int flag, int j);
void parsing(t_mini *mini, char *str);
void ft_exit(t_mini *mini);

/* ************************************************************************** */
/*				                 pipes                              	      */
/* ************************************************************************** */

/* ************************************************************************** */
/*				checker					   */
/* ************************************************************************** */
int check_position(t_mini *mini, int j);
/* ************************************************************************** */
/*				                      signal	             				  */
/* ************************************************************************** */
void	signals_start(void);
void	exec_signals(int sig, void *mini);

void ft_init_signals(void);
void ft_ignore_signals(void);
void ft_restore_signals(void);
void ft_handle_eof(void);
void ft_handle_sigint(int sig);
void ft_handle_sigint_ign(int sig);
void ft_handle_sigquit(int sig);


void	handle_sigint();
/* ************************************************************************** */
/*				parser.c					   */
/* ************************************************************************** */

int check_position_bool(t_mini *mini, char *to_find);
void through_pipes(t_mini *mini, int i);
void close_pipes(t_mini *mini);
void get_exit_status(t_mini *mini);
void ft_handle_eof(void);
void free_struct(t_mini *mini);
void free_struct_2(t_mini *mini);
int check_inutils(t_mini *mini);
char *ft_remove_quotes(char *str);
int count_quotes(char *str);
char *ft_remove_quotes(char *str);
int check_parser2(t_mini *mini, int i);
int check_parser(t_mini *mini);
void while_loop(char **s);
void hanlde_redirects(t_mini *mini);
void redirect(t_mini *mini);
void parser(t_mini *mini);
char *do_sum(t_mini *mini, int i);
int check_parser3(t_mini *mini, int i);
void handle_red(t_mini *mini, int i);
void handle_append(t_mini *mini, int i);
void handle_heredoc(t_mini *mini, int i);
int free_child_p(t_mini *mini);
int handle_heredoc2(char *delimiter);
void unlink_all(void);
int do_redirects(t_mini *mini, int i);
int count_red(t_mini *mini);
char **add_option(t_mini *mini, int i);
int print_pwd(void);
char *get_expand(char *s);
int check_expand(t_mini *mini);
int bingo(char *s, char c);
char *ft_before(char *);
char *ft_after(char *);
void free_expand(char *s1, char *s2, char *s3, int flag);
void do_strjoin(int i, char *env, t_mini *mini);
char *ft_touppercase(char *s);
void do_strdup(int i, char *env, t_mini *mini, int flag);
bool is_a_append_here(char *s);
bool is_a_folder(char *s);
int count_dquotes(char *str);
int get_envp(t_mini *mini);
int get_export(t_mini *mini);
char **add_var(char **newenvp, char *new_var);
void export_woquotes(char **newvar, t_mini *mini);
void export_quotes(char **newvar, t_mini *mini);
char *ft_strcpy(char *dest, char *src);
int fore(char *s);
int afta(char *s);
char *help(char *str);
int get_unset(t_mini *mini);
int check_next(t_mini *mini, int i);
int var_exists(t_mini *mini, char *var);
char **which_split(char *str, t_mini *mini);
char **echo_split(char const *s, char c);
void delete_replace(t_mini *mini, char **str);
char *get_var(char *s);
char **remove_var(char **newenvp, char *var_name);
int count_squotes(char *str);
int ft_after_exp(char *str, int j);
void out_of_names(char *s);
int ft_before_exp(char *str);
int ft_var(char *str);
bool is_a_number(char *s);
char **another_split(t_mini *mini, int i);
char *give_first(char *no_quotes, t_mini *mini, int i);
void check_comand(t_mini *mini);

#endif
