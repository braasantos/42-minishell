#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
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
	char *cmd;
	char **cmd1;
	char *wrongarg;
	char *str;
	char **newenvp;
	char **args;
	pid_t newpro;
	pid_t child1;
	pid_t child2; // new_process - for the fork
	char *new_str;
	int end[2];
} t_mini;

int ft_strcmp(char *str1, char *str2);
void parsing(t_mini *mini);
// void new_string(char *str, t_mini *mini);
void print(t_op op, char *ag);
void get_cd(char *args, t_mini *mini);
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
void second_c(t_mini *mini, int i, int count);
void ft_child1(t_mini *mini);
void ft_child2(t_mini *mini);
int exec_pipes(t_mini *mini);
void put_cmd(t_mini *mini);
void builtins(t_mini *mini);
void get_cd(char *args, t_mini *mini);

#endif