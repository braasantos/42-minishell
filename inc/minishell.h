/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 12:07:24 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/19 16:57:00 by bjorge-m         ###   ########.fr       */
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
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../includes/LIBFT/libft.h"

extern int	g_signal;

# define STX_ERROR	"Minishell: syntax error near unexpected token `newline'"

typedef enum e_op
{
	COMMAND_NOT_FOUND,
	NO_SUCH_FILE_OR_DIR,
	NO_PERMISSION,
	IS_DIR,
}		t_op;

typedef struct s_split
{
	int		i;
	int		start;
	char	**s;
	char	**temp;
	bool	quotes;
	int		words;
	int		tokens;
}		t_split;

typedef struct s_mini
{
	char	*path_to_cmd;
	char	**exec_args;
	char	**newenvp;
	char	**args;
	pid_t	*newpro;
	char	*str;
	char	*pwd;
	char	*new_str;
	int		*pipes_fd;
	char	**echo_split;
	char	**another_split;
	int		fd1;
	int		fd0;
	int		st_din;
	int		st_dout;
	int		stdin_fd;
	int		stdout_fd;
	int		flag;
	int		echo_flag;
	int		exit_flag;
	char	*before;
	char	*after;
	int		free_flag;
	int		flag_echo;
	bool	pipe_or_redirect_found;
	bool	interact;
}		t_mini;

/* ************************************************************************** */
/*			                    builtins	                   				  */
/* ************************************************************************** */
/* ******************** */
/* 		builtins.c		*/
/* ******************** */
int		str_len(char **str);
int		have_redirect(t_mini *mini);
int		builtins(t_mini *mini, int i);
int		check_parser2(t_mini *mini, int i);
bool	is_a_builtin(t_mini *mini, int i);
/* ******************** */
/* 		cd_util.c		*/
/* ******************** */
int		find_env_var(char *var, t_mini *mini);
char	**realloc_envv(int new_size, t_mini *mini);
void	set_env_var(char *key, char *value, t_mini *mini);
int		ft_strendswith(char *s1, char *s2);
char	*ft_pathjoin(char *p1, char *p2);
/* ******************** */
/* 			cd.c		*/
/* ******************** */
char	*get_env(char *var, t_mini *mini);
void	change_dir(char *path, t_mini *mini);
int		get_cd(t_mini *mini, int i);
int		ft_strstartswith(char *s1, char *s2);
/* ******************** */
/* 		new_split.c		*/
/* ******************** */
int		new_split(char *str, t_mini *mini);
/* ******************** */
/* 		echo_utils.c	*/
/* ******************** */
int		handle_split_args(t_mini *mini, int i);
void	check_comand(t_mini *mini);
int		count_dquote_pairs(char *str);
int		count_squote_pairs(char *str);
char	**forming_echo_args(char **s, int i);
int		condition_to_expand(t_mini *mini, int i);
/* ******************** */
/* 		echo.c			*/
/* ******************** */
void	print_arg(char *str, int current, int flag, char **args);
int		echo_cmd(char **tokens, t_mini *mini);
void	ft_print_new_line(int flag_nl);
bool	db_quotes(char *str);
/* ******************** */
/* 			env			*/
/* ******************** */
int		get_envp(t_mini *mini);
/* ******************** */
/* 		expander.c		*/
/* ******************** */
char	*get_expand(char *s);
void	time_to_remove(t_mini *mini, int i);
void	ohhh_boy(t_mini *mini, int i);
int		expand_str(t_mini *mini, int i);
void	do_all(t_mini *mini, int i, char *env);
/* ******************** */
/* 		expander2.c		*/
/* ******************** */
void	do_strjoin(int i, char *env, t_mini *mini);
void	free_expand(char *s1, char *s2, char *s3, int flag);
int		ft_var(char *str);
char	*ft_before(char *s);
char	*ft_after(char *s);
/* ******************** */
/* 		export_utils.c		*/
/* ******************** */
char	*ft_strcpy(char *dest, const char *src);
int		fore(char *s);
int		afta(char *s);
char	*help(char *str);
int		ft_before_exp(char *str);
/* ******************** */
/* 		export_utils.c		*/
/* ******************** */
char	**get_alpha(char **str);
char	*export_no_option_util(char *s);
// char	**bb_sort(char **s);
void	export_no_option(t_mini *mini);
/* ******************** */
/* 		export.c		*/
/* ******************** */
char	**add_var(char **newenvp, char *new_var);
char	*get_var(char *s);
int		export_unset(t_mini *mini, int i);
void	export_woquotes(char **newvar, t_mini *mini, int i);
char	*ft_remove_squotes(const char *str);
/* ******************** */
/* 		export2.c		*/
/* ******************** */
void		get_export(t_mini *mini);
int		var_exists(t_mini *mini, char *var);
void	delete_replace(t_mini *mini, char **str, int i, int *flag);
void	export_quotes(char **newvar, t_mini *mini, int i);
/* ******************** */
/*		   pwd.c		*/
/* ******************** */
int		print_pwd(t_mini *mini);
/* ******************** */
/* 		unset.c			*/
/* ******************** */
char	**remove_var(char **newenvp, char *var_name);
int		get_unset(t_mini *mini);
bool	is_space(char c);
/* ************************************************************************** */
/*								clean_exit									  */
/* ************************************************************************** */
/* ******************** */
/* 	    clean_all.c		*/
/* ******************** */
void	ft_free_arr(char **str);
void	free_struct(t_mini *mini);
void	free_struct_2(t_mini *mini);
int		arg_number(t_mini *mini);
int		check_signals(char *arg);
int		get_exit_number(char *str);
/* ************************************************************************** */
/*								execution	    							  */
/* ************************************************************************** */
/* ******************** */
/* 	    exec_utils.c	*/
/* ******************** */
void	handle_append2(t_mini *mini, int i);
int		check_here(t_mini *mini);
void	ft_exit_builtin(t_mini *mini, int i);
void	print_cmd(t_mini *mini, int i);
void	handle_execve(t_mini *mini, int i);
/* ******************** */
/*			exec.c		*/
/* ******************** */
int		execute(t_mini *mini);
int		pipe_creation(t_mini *mini);
bool	is_not_a_cmd(char *s);
void	create_flow(t_mini *mini);
int		create_child(t_mini *mini, int i, int flag, int j);
/* ************************************************************************** */
/*								helpers 	    							  */
/* ************************************************************************** */
/* ******************** */
/*	checkers_tuils.c	*/
/* ******************** */
char	*do_sum(t_mini *mini, int i);
int		count_quotes(char *str);
int		count_dquotes(char *str);
/* ******************** */
/*		checkers.c		*/
/* ******************** */
bool	is_a_pipe(char *s, int flag);
bool	is_a_red(char *s);
bool	is_a_cmd(char *s, t_mini *mini);
bool	is_a_file(char *s);
bool	is_a_option(char *s, t_mini *mini);
/* ******************** */
/*	parser_helpers.c	*/
/* ******************** */
void	pad(char *src, char *dest, int i, int j);
int		padding_needed(char *str, int i, int pad);
char	*pad_central(char *str);
int		check_position_bool(t_mini *mini, char *to_find);
int		check_position(t_mini *mini, int j);
/* ******************** */
/*		path_helpers.c	*/
/* ******************** */
void	update_path(t_mini *mini, int i);
char	*hndl_quotes(t_mini *mini, int i);
char	**add_option(t_mini *mini, int i, char *temp);
int		save_lines2(t_mini *mini, char *temp, int i);
void	delete_path(t_mini *mini);
/* ******************** */
/*		utils.commands.c	*/
/* ******************** */
char	*ft_add(t_mini *mini, char *ag);
char	**get_path(char **newenv);
char	**get_newenvp(char **envp);
bool	is_a_append_here(char *s);
bool	is_a_number(char *s);
/* ******************** */
/*		utils.c			*/
/* ******************** */
int		find_char(char c, char *find);
int		quotes_open(char *str, int target_index);
int		pipe_check(t_mini *mini, char *str);
int		redirect_basic_check(char *str);
bool	check_options(char *s);
/* ******************** */
/*		utils2.c		*/
/* ******************** */
int		ft_check_open_quotes(char *str);
int		print(t_op op, char *ag);
int		check_args(char *str);
int		ft_strcmp(char *str1, char *str2);
bool	is_a_folder(char *s);
/* ******************** */
/*		utils3.c		*/
/* ******************** */
int		check_parser(t_mini *mini);
int		check_parser3(t_mini *mini, int i);
int		do_redirects(t_mini *mini, int i);
char	*ft_remove_quotes(char *str);
int		check_next(t_mini *mini, int i);
/* ******************** */
/*		utils4.c		*/
/* ******************** */
int		count_squotes(char *str);
void	while_loop(char **s);
char	*ft_touppercase(char *s);
int		print_error(char *s);
/* ******************** */
/*		utils5.c		*/
/* ******************** */
void	twenty_six_lines(t_mini *mini);
char	*export_var(char *s);
int		export_key_util(char *s);
char	*export_key(char *s);
int		get_qmark(t_mini *mini, int i);
/* ******************** */
/*		utils6.c		*/
/* ******************** */
int		have_here_doc(t_mini *mini);
void	do_shlvl(t_mini *mini);
/* ************************************************************************** */
/*								parsing									  */
/* ************************************************************************** */
/* ******************** */
/*		parsing.c		*/
/* ******************** */
// void	ft_exit(t_mini *mini, int i);
int		bingo(char *s, char c);
int		parsing(t_mini *mini, char *str);
void	sigint_on_child(int signal);
void	get_exit_status(t_mini *mini);
/* ************************************************************************** */
/*								pipes										  */
/* ************************************************************************** */
/* ******************** */
/*			pipes.c		*/
/* ******************** */
void	through_pipes(t_mini *mini, int i, int flag);
int		count_pipes(t_mini *mini);
void	close_pipes(t_mini *mini);
/* ************************************************************************** */
/*								redirects									  */
/* ************************************************************************** */
/* ******************** */
/*	append_heredoc.c	*/
/* ******************** */
int		handle_red(t_mini *mini, char *s, char *ss, int flag);
int		handle_append(char *s);
int		handle_heredoc(t_mini *mini, char *s);
int		handle_heredoc2(char *delimiter, t_mini *mini);

/* ******************** */
/*		redirects.c	    */
/* ******************** */
int		count_red(t_mini *mini);
int		redirect_output(char *s, t_mini *mini);
int		redirect_input(char *s);
int		hanlde_redirects(t_mini *mini, char **s, int i, int flag);
void	redirect(t_mini *mini);
/* ************************************************************************** */
/*								signals									  */
/* ************************************************************************** */
/* ******************** */
/*	signal_handlers.c	*/
/* ******************** */
void	backslash(int sig);
void	ctrl_c(int sig);
void	back_to_prompt(int sig);
void	signals(int sig, t_mini *mini);
/* ************************************************************************** */
/*									main									  */
/* ************************************************************************** */
void	parser(t_mini *mini);
int		file_ok(char *s, int flag);
int		null_args(t_mini *mini, int i);
void	exit_fork(t_mini *mini);
int		check_env(t_mini *mini);
int		pre_echo(t_mini *mini, int i);
bool	is_a_quote(char *s);
void	update_pwd(t_mini *mini);
int		export_len(char **s);
char	*ft_remove_dquotes(const char *str);
char	**echo_w_red(char **s);
int		export_len(char **s);
int		get_grep(t_mini *mini, int i);
int		have_redi(char **s);
int		check_pos_str(char **s);
char	**new_args(char **s, int k, int k1);
void	check_echo(t_mini *mini);
int		count_files(char **s);
int		check_parser_full(t_mini *mini);
int		heredoc_first(t_mini *mini, int flag);
int		check_empty(t_mini *mini);
int		builtins_check(t_mini *mini, int i);
int		check_here(t_mini *mini);
int		remove_str(t_mini *mini, int i);
int		havehere_doc(char **s);
int		check_pwd(char *s, t_mini *mini);
int		im_done_parser(t_mini *mini);
int		count_dquote_pairs(char *str);

//error
int		ft_fprintf(int fd, const char *format, ...);
int		pipe_or_append(char *s);
void	signals_child(void);
int		check_things(char *s);
int		last_to_find(char **s, char *to_find);
int		count_here(char **str, char *to_find);
char	*ft_strncpy(char *dest, const char *src, size_t num);
void	take_care(t_mini *mini, int flag, char **s);
int		red_out(t_mini *mini);
int		remove_quotes_exp(t_mini *mini, int i);
void	free_expand2(t_mini *mini, int flag, int i);
void	ft_init_signals(void);
void	ft_doc_signals(void);
void	ft_ignore_signals(void);
void	exit_fork_here_doc(t_mini *mini);
int		here_doc_ver(t_mini *mini, int i);
int		rem_heredoc(t_mini *mini);

#endif
