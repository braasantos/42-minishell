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
	char *path_to_cmd;
	char **exec_args;
	char **cmd1;
	char *cmd;
	char *str;
	char **newenvp;
	char **args;
	pid_t newpro;
	pid_t child1;
	pid_t child2; // new_process - for the fork
	char *new_str;
	int end[2];
	int fd1;
	int fd0;
} t_mini;

int ft_strcmp(char *str1, char *str2);
void parsing(t_mini *mini, char *str);
// void new_string(char *str, t_mini *mini);
void print(t_op op, char *ag);
int get_cd(t_mini *mini);
int check_args(char *str);
char **get_newenvp(char **envp);
char **get_path(char **newenv);
char *ft_add(t_mini *mini, char *ag);
void ft_handle_sigint(int sig);
void ft_handle_sigint_ign(int sig);
void ft_handle_sigquit(int sig);
void ft_restore_signals(void);
void ft_ignore_signals(void);
void ft_init_signals(void);
void ft_exit(t_mini *mini);
// void ft_close1(t_mini *mini);
// void ft_close2(t_mini *mini);
// void ft_closefinal(t_mini *mini);
void second_c(t_mini *mini);
void ft_child1(t_mini *mini);
void ft_child2(t_mini *mini);
int exec_pipes(t_mini *mini);
void put_cmd(t_mini *mini, char *str);
int builtins(t_mini *mini);
int redirect_cmd(t_mini *mini);
int execute_rd_one(t_mini *mini);
int check_commands(t_mini *mini);
int count_pipes(t_mini *mini);
int str_len(char **str);
int check_red(t_mini *mini);
// void close_fd(int fd);
int ft_check_open_quotes(char *str);
int redirect_basic_check(char *str);
int quotes_open(char *str, int target_index);
int pipe_check(char *str);
int padding_needed(char *str, int i, int pad);
int find_char(char c, char *find);
char *pad_central(char *str);
void pad(char *src, char *dest, int i, int j);

int ft_strstartswith(char *s1, char *s2);
// char *get_env(char *var, t_mini *mini);
// char *parse_home_path(char *path, int reverse_parse, t_mini *mini);
// void print_pth(char *path, t_mini *mini);
void change_dir(char *path, t_mini *mini);
char *ft_pathjoin(char *p1, char *p2);
int ft_strendswith(char *s1, char *s2);
void set_env_var(char *key, char *value, t_mini *mini);
char **realloc_envv(int new_size, t_mini *mini);
int find_env_var(char *var, t_mini *mini);

int echo_cmd(char **args);
int ft_check_echo_arguments(char *args);
void ft_print_echo_space(char **aux);
void ft_print_new_line(int flag_nl);

void execute(t_mini *mini);
int check_position(t_mini *mini, char *to_find);
int change_ends_red(t_mini *mini, int flag);
void create_child(t_mini *mini);
int have_redirect(t_mini *mini);
void close_fd(t_mini *mini, int fd, int flag);

void execute_second(t_mini *mini);
void red_pipes(t_mini *mini, int i);

void create_flow(t_mini *mini);

#endif