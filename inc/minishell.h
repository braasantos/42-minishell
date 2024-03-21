/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 12:07:24 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/03/18 12:15:43 by bjorge-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdbool.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../includes/LIBFT/libft.h"

extern int	g_signal;

typedef enum e_op
{
	COMMAND_NOT_FOUND,
}		t_op;

typedef struct s_mini
{
<<<<<<< HEAD
	char	*path_to_cmd;
	char	**exec_args;
	char	**newenvp;
	char	**args;
	pid_t	*newpro;
	char	*str;
	char	*new_str;
	int		*pipes_fd;
	char	**echo_split;
	int		fd1;
	int		fd0;
	int		STDIN;
	int		STDOUT;
	int		stdin_fd;
	int		stdout_fd;
	int		flag;
	int		echo_flag;
	int		exit_flag;
	char	*before;
	char	*after;
	int		free_flag;
	bool	pipe_or_redirect_found;
	bool	interact;
}		t_mini;

/* ************************************************************************** */
/*                                builtins	                              */
/* ************************************************************************** */

int		str_len(char **str);
int		have_redirect(t_mini *mini);
int		builtins(t_mini *mini, int i);
int		find_env_var(char *var, t_mini *mini);
char	**realloc_envv(int new_size, t_mini *mini);
void		set_env_var(char *key, char *value, t_mini *mini);
int		ft_strendswith(char *s1, char *s2);
char	*ft_pathjoin(char *p1, char *p2);
char	*get_env(char *var, t_mini *mini);
void		change_dir(char *path, t_mini *mini);
int		get_cd(t_mini *mini, int i);
int		ft_strstartswith(char *s1, char *s2);
int		echo_cmd(char **tokens, t_mini *mini);
int		ft_check_echo_arguments(char *array_args);
void		ft_print_new_line(int flag_nl);

=======
	char *path_to_cmd;
	char **exec_args;
	char **newenvp;
	char **args;
	pid_t *newpro;
	char *str;
	char *new_str;
	int *pipes_fd;
	char **echo_split;
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
	int free_flag;
	bool pipe_or_redirect_found;
	bool interact;
} t_mini;

/* ************************************************************************** */
/*			                    builtins	                   				  */
/* ************************************************************************** */
/* ******************** */
/* 		builtins.c		*/
/* ******************** */
int str_len(char **str);
int have_redirect(t_mini *mini);
int builtins(t_mini *mini, int i);
int check_parser2(t_mini *mini, int i);
bool is_a_builtin(t_mini *mini, int i);
/* ******************** */
/* 		cd_util.c		*/
/* ******************** */
int find_env_var(char *var, t_mini *mini);
char **realloc_envv(int new_size, t_mini *mini);
void set_env_var(char *key, char *value, t_mini *mini);
int ft_strendswith(char *s1, char *s2);
char *ft_pathjoin(char *p1, char *p2);
/* ******************** */
/* 			cd.c		*/
/* ******************** */
char *get_env(char *var, t_mini *mini);
void change_dir(char *path, t_mini *mini);
int get_cd(t_mini *mini, int i);
int ft_strstartswith(char *s1, char *s2);
/* ******************** */
/* 		echo_split.c	*/
/* ******************** */
char **echo_split(char const *s, char c);
/* ******************** */
/* 		echo_utils.c	*/
/* ******************** */
char **add_option_echo(t_mini *mini, int i, char *temp);
void handle_split_args(t_mini *mini);
void check_comand(t_mini *mini);
char **which_split(char *str, t_mini *mini);
int count_quote_pairs(char *str);
/* ******************** */
/* 		echo.c			*/
/* ******************** */
void print_arg(char *str, t_mini *mini, int current, int flag);
int echo_cmd(char **tokens, t_mini *mini);
void ft_print_new_line(int flag_nl);
int redirect_output_echo(int i, t_mini *mini);
bool db_quotes(char *str);
/* ******************** */
/* 			env			*/
/* ******************** */
int get_envp(t_mini *mini);
/* ******************** */
/* 		expander.c		*/
/* ******************** */
char *get_expand(char *s);
void time_to_remove(t_mini *mini, int i);
void ohhh_boy(t_mini *mini, int i);
void expand_str(t_mini *mini, int i);
void do_all(t_mini *mini, int i, char *env);
/* ******************** */
/* 		expander2.c		*/
/* ******************** */
void do_strjoin(int i, char *env, t_mini *mini);
void free_expand(char *s1, char *s2, char *s3, int flag);
int ft_var(char *str);
char *ft_before(char *s);
char *ft_after(char *s);
/* ******************** */
/* 		export_utils.c		*/
/* ******************** */
char *ft_strcpy(char *dest, char *src);
int fore(char *s);
int afta(char *s);
char *help(char *str);
int ft_before_exp(char *str);
/* ******************** */
/* 		export.c		*/
/* ******************** */
char **add_var(char **newenvp, char *new_var);
char *get_var(char *s);
int export_unset(t_mini *mini);
void export_woquotes(char **newvar, t_mini *mini);
char *ft_remove_squotes(const char *str);
/* ******************** */
/* 		export2.c		*/
/* ******************** */
int get_export(t_mini *mini);
int var_exists(t_mini *mini, char *var);
void delete_replace(t_mini *mini, char **str);
void export_quotes(char **newvar, t_mini *mini);
/* ******************** */
/*		   pwd.c		*/
/* ******************** */
int print_pwd(t_mini *mini, int i);
/* ******************** */
/* 		unset.c			*/
/* ******************** */
char **remove_var(char **newenvp, char *var_name);
int get_unset(t_mini *mini);
bool is_space(char c);
>>>>>>> refs/remotes/origin/master
/* ************************************************************************** */
/*								clean_exit									  */
/* ************************************************************************** */
<<<<<<< HEAD

void		execute(t_mini *mini);
void		create_flow(t_mini *mini);

=======
/* ******************** */
/* 	    clean_all.c		*/
/* ******************** */
void ft_free_arr(char **str);
void free_struct(t_mini *mini);
void free_struct_2(t_mini *mini);
/* ************************************************************************** */
/*								execution	    							  */
/* ************************************************************************** */
/* ******************** */
/* 	    exec_utils.c	*/
/* ******************** */
void handle_append2(t_mini *mini, int i);
int check_here(t_mini *mini);
void ft_exit_builtin(t_mini *mini, int i);
/* ******************** */
/*			exec.c		*/
/* ******************** */
void execute(t_mini *mini);
int pipe_creation(t_mini *mini);
bool is_not_a_cmd(char *s);
void create_flow(t_mini *mini);
int create_child(t_mini *mini, int i, int flag, int j);
>>>>>>> refs/remotes/origin/master
/* ************************************************************************** */
/*								helpers 	    							  */
/* ************************************************************************** */
<<<<<<< HEAD

bool		is_a_option(char *s, t_mini *mini);
bool		is_a_file(char *s);
bool		is_a_cmd(char *s, t_mini *mini);
bool		is_a_red(char *s);
bool		is_a_pipe(char *s);
char	**split_to_split(t_mini *mini, int i);
void		create_file(t_mini *mini);
bool		is_a_file_to_create(char *s, t_mini *mini);
void		update_path(t_mini *mini, int i);
void		delete_path(t_mini *mini);
void		pad(char *src, char *dest, int i, int j);
int		find_char(char c, char *find);
int		padding_needed(char *str, int i, int pad);
char	*pad_central(char *str);
int		quotes_open(char *str, int target_index);
int		pipe_check(t_mini *mini, char *str);
int		redirect_basic_check(char *str);
int		ft_check_open_quotes(char *str);
int		count_pipes(t_mini *mini);
int		print(t_op op, char *ag);
int		check_args(char *str);
int		ft_strcmp(char *str1, char *str2);
char	**get_newenvp(char **envp);
char	**get_path(char **newenv);
char	*ft_add(t_mini *mini, char *ag);
void		ft_free_arr(char **str);

/* ************************************************************************** */
/*				parser.c					   */
/* ************************************************************************** */
int		create_child(t_mini *mini, int i, int flag, int j);
void		parsing(t_mini *mini, char *str);
void		ft_exit(t_mini *mini);

/* ************************************************************************** */
/*				                 pipes                              	      */
/* ************************************************************************** */

/* ************************************************************************** */
/*				checker					   */
/* ************************************************************************** */
int		check_position(t_mini *mini, int j);
/* ************************************************************************** */
/*				                      signal	             				  */
/* ************************************************************************** */
void		signals_start(void);
void		exec_signals(int sig, void *mini);

void		ft_init_signals(void);
void		ft_ignore_signals(void);
void		ft_restore_signals(void);
void		ft_handle_eof(void);
void		ft_handle_sigint(int sig);
void		ft_handle_sigint_ign(int sig);
void		ft_handle_sigquit(int sig);

void handle_sigint();
/* ************************************************************************** */
/*				parser.c					   */
/* ************************************************************************** */

int		check_position_bool(t_mini *mini, char *to_find);
void		through_pipes(t_mini *mini, int i);
void		close_pipes(t_mini *mini);
void		get_exit_status(t_mini *mini);
void		ft_handle_eof(void);
void		free_struct(t_mini *mini);
void		free_struct_2(t_mini *mini);
int		check_inutils(t_mini *mini);
char	*ft_remove_quotes(char *str);
int		count_quotes(char *str);
char	*ft_remove_quotes(char *str);
int		check_parser2(t_mini *mini, int i);
=======
/* ******************** */
/*	checkers_tuils.c	*/
/* ******************** */
bool is_a_file_to_create(char *s, t_mini *mini);
void create_file(t_mini *mini);
char *do_sum(t_mini *mini, int i);
int count_quotes(char *str);
int count_dquotes(char *str);
/* ******************** */
/*		checkers.c		*/
/* ******************** */
bool is_a_pipe(char *s);
bool is_a_red(char *s);
bool is_a_cmd(char *s, t_mini *mini);
bool is_a_file(char *s);
bool is_a_option(char *s, t_mini *mini);
/* ******************** */
/*	parser_helpers.c	*/
/* ******************** */
void pad(char *src, char *dest, int i, int j);
int padding_needed(char *str, int i, int pad);
char *pad_central(char *str);
int check_position_bool(t_mini *mini, char *to_find);
int check_position(t_mini *mini, int j);
/* ******************** */
/*		path_helpers	*/
/* ******************** */
void update_path(t_mini *mini, int i);
char *hndl_quotes(t_mini *mini, int i);
char **add_option(t_mini *mini, int i, char *temp);
int save_lines2(t_mini *mini, char *temp, int i);
void delete_path(t_mini *mini);
/* ******************** */
/*		utils.commands	*/
/* ******************** */
char *ft_add(t_mini *mini, char *ag);
char **get_path(char **newenv);
char **get_newenvp(char **envp);
bool is_a_append_here(char *s);
bool is_a_number(char *s);

/* ******************** */
/*		utils.c			*/
/* ******************** */
int find_char(char c, char *find);
int quotes_open(char *str, int target_index);
int pipe_check(t_mini *mini, char *str);
int redirect_basic_check(char *str);
bool check_options(char *s);
/* ******************** */
/*		utils2.c		*/
/* ******************** */
int ft_check_open_quotes(char *str);
int print(t_op op, char *ag);
int check_args(char *str);
int ft_strcmp(char *str1, char *str2);
bool is_a_folder(char *s);
/* ******************** */
/*		utils3.c		*/
/* ******************** */
>>>>>>> refs/remotes/origin/master
int check_parser(t_mini *mini);
int check_parser3(t_mini *mini, int i);
int do_redirects(t_mini *mini, int i);
char *ft_remove_quotes(char *str);
int check_next(t_mini *mini, int i);
/* ******************** */
/*		utils4.c		*/
/* ******************** */
int count_squotes(char *str);
void while_loop(char **s);
char *ft_touppercase(char *s);
/* ************************************************************************** */
/*								parsing.c									  */
/* ************************************************************************** */
/* ******************** */
/*		parsing.c		*/
/* ******************** */
void ft_exit(t_mini *mini);
int bingo(char *s, char c);
void parsing(t_mini *mini, char *str);
void sigint_on_child(int signal);
void get_exit_status(t_mini *mini);
/* ************************************************************************** */
/*								pipes.c										  */
/* ************************************************************************** */
/* ******************** */
/*			pipes.c		*/
/* ******************** */
void through_pipes(t_mini *mini, int i);
int count_pipes(t_mini *mini);
void close_pipes(t_mini *mini);
/* ************************************************************************** */
/*								redirects.c									  */
/* ************************************************************************** */
/* ******************** */
/*	append_heredoc.c	*/
/* ******************** */
void handle_red(t_mini *mini, int i);
void handle_append(t_mini *mini, int i);
void handle_heredoc(t_mini *mini, int i);
int free_child_p(t_mini *mini);
int handle_heredoc2(char *delimiter);
/* ******************** */
/*		redirects.c	    */
/* ******************** */
int count_red(t_mini *mini);
<<<<<<< HEAD
char **add_option(t_mini *mini, int i, char *temp);
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
void		check_comand(t_mini *mini);
void		expand_str(t_mini *mini, int i);
void		do_all(t_mini *mini, int i, char *env);
void		time_to_remove(t_mini *mini, int i);
int		count_quote_pairs(char *str);
bool		is_not_a_cmd(char *s);
void		ohhh_boy(t_mini *mini, int i);
bool		is_a_builtin(t_mini *mini, int i);
char	*hndl_quotes(t_mini *mini, int i);
int		save_lines2(t_mini *mini, char *temp, int i);
bool		check_options(char *s);
int		redirect_output(int i, t_mini *mini);
int		redirect_output_echo(int i, t_mini *mini);
void		handle_split_args(t_mini *mini);
=======
int redirect_output(int i, t_mini *mini);
int redirect_input(int i, t_mini *mini);
void hanlde_redirects(t_mini *mini);
void redirect(t_mini *mini);
/* ************************************************************************** */
/*								signals.c									  */
/* ************************************************************************** */
/* ******************** */
/*	signal_handlers.c	*/
/* ******************** */
void exec_signals(int sig, void *mini);
void signals_start(void);
/* ************************************************************************** */
/*									main.c									  */
/* ************************************************************************** */
void parser(t_mini *mini);
>>>>>>> refs/remotes/origin/master
#endif
