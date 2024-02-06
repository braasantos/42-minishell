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

typedef enum e_op
{
	COMMAND_NOT_FOUND,
} t_op;

typedef struct s_mini
{
	char *cmd;
	char **newenvp;
	char **args;
	pid_t newpro; // new_process - for the fork
	char *new_str;
} t_mini;

int ft_strcmp(char *str1, char *str2);
void parsing(t_mini *mini, char *str);
void new_string(char *str, t_mini *mini);
void print(t_op op, char *ag);
void get_cd(char *args);
int check_args(char *str);
char **get_newenvp(char **envp);
char **get_path(char **newenv);
char *ft_add(char **newenvp, char *ag);
#endif