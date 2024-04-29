/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjorge-m <bjorge-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:33:02 by bjorge-m          #+#    #+#             */
/*   Updated: 2024/04/26 13:05:41 by bjorge-m         ###   ########.fr       */
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
# include <stdarg.h>
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
	char	**string;
	int		i;
	int		start;
	bool	quotes;
	char	quote;
	int		j;
	int		len;
}		t_split;

typedef struct s_mini
{
	char	*path_to_cmd;
	char	**exec_args;
	char	**envp;
	char	**args;
	pid_t	*newpro;
	char	*str;
	char	*pwd;
	char	*new_str;
	int		*pipes_fd;
	char	**echo_split;
	char	*new_delimiter;
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

char	**ft_newsplit(char *str, t_split split);
char	*ft_remove_quotes(char *str);
int		condition_to_expand(int i, char **s);
int		bingo(char *s, char c);
char	**check_empty(char **args);
int		command(t_mini *mini, char **str);
int		doredirect(char ***s, t_mini *mini);
int		count_pipes(char **str);
int		count_files(char **s);
int		ft_check_open_quotes(char *str);
int		redirect_check(char *str);
void	check_comand(char **s, t_mini *mini);
void	remove_quotes_helper(char **str, int i);
int		count_quotes(char *str);
bool	is_a_cmd(char *s, t_mini *mini);
bool	is_a_file(char *s);
bool	is_a_folder(char *s);
char	**ft_arrcpy(char **envp);
int		ft_fprintf(int fd, const char *format, ...);
void	ft_free_arr(char **str);
void	parser(t_mini *mini);
char	*add_space(char *str);
int		parser_util(char *str);
int		handle_tokens(t_mini *mini);
int		find_char(char c, char *find);
int		quotes_open(char *str, int target_index);
char	*ft_add(t_mini *mini, char *ag);
bool	is_a_quote(char *s);
int		arr_len(char **str);
char	*ft_strcpy(char *dest, const char *src);
int		ft_strcmp(char *str1, char *str2);
int		remove_str(char ***str, int i);
void	while_loop(char **s);
char	*get_env(char *var, t_mini *mini);
int		check_pwd(char *s, t_mini *mini);
int		ft_strstartswith(char *s1, char *s2);
char	**remove_var(char **newenvp, char *var_name);
bool	check_options(char *s);
bool	is_a_pipe(char *s);
bool	is_a_red(char *s);
bool	is_a_append_here(char *s);
void	print_error(int flag, char *s);
int		expand_str(t_mini *mini, int i, char **str);
int		count_squotes(char *str);
int		checking(t_mini *mini);
int		parser_util(char *str);
int		check_all_redirects(char **str);
void	print_error(int flag, char *s);
int		check_pipe(char **str, int i);
int		check_heredoc(char **str, int i);
char	*ft_strncpy(char *dest, const char *src, size_t num);
char	*ft_remove_dquotes(const char *str);
int		count_dquote_pairs(char *str);
int		count_squote_pairs(char *str);
char	*ft_remove_squotes(const char *str);
void	remove_d_quotes(char **str, int i, char *s);
void	remove_s_quotes(char **str, int i, char *s);
void	time_to_remove(char **str, int i);
void	free_all(t_mini *mini);
int		ft_newsplit_len(char *str);
int		change_args(t_mini *mini, char ***args);
int		ft_isspace(char *s);
void	free_struct(t_mini *mini);
int		check_env(t_mini *mini);
int		chech_path(char *s);
void	update_envs(char *cwd, t_mini *mini);
void	change_dir(char *path, t_mini *mini);
int		get_cd(t_mini *mini, int i);
int		find_env_var(char *var, t_mini *mini);
char	**realloc_envv(int new_size, t_mini *mini);
int		ft_strendswith(char *s1, char *s2);
char	*ft_pathjoin(char *p1, char *p2);
int		ft_strstartswith(char *s1, char *s2);
void	set_env_var(char *key, char *value, t_mini *mini);
void	update_pwd(t_mini *mini);
void	do_shlvl(t_mini *mini);
int		check_pwd(char *s, t_mini *mini);
char	*export_key(char *s);
int		export_key_util(char *s);
char	*export_var(char *s);
int		print_pwd(t_mini *mini);
int		execute(t_mini *mini);
int		builtins(t_mini *mini, int i);
int		handle_heredoc(char *s, t_mini *mini);
int		heredoc_first(t_mini *mini);
int		handle_heredoc2(char *delimiter, t_mini *mini);
void	exit_fork_here_doc(t_mini *mini);
void	redirect(t_mini *mini);
int		command(t_mini *mini, char **s);
int		get_envp(t_mini *mini, int i);
void	get_export(t_mini *mini);
int		export_len(char **s);
int		count_quotes(char *str);
int		count_dquotes(char *str);
void	delete_replace(t_mini *mini, char **str, int i, int *flag);
void	export_quotes(char **newvar, t_mini *mini, int i);
int		pipe_or_append(char *s);
void	export_no_option(t_mini *mini);
char	*get_var(char *s);
void	export_woquotes(char **newvar, t_mini *mini, int i);
char	**get_alpha(char **str);
char	*export_no_option_util(char *s);
int		export_wo_equal(char *s, char *c);
int		export_unset(t_mini *mini, int i);
char	**add_var(char **newenvp, char *new_var);
int		get_unset(t_mini *mini);
int		handle_split_args(t_mini *mini, int i);
void	check_echo(t_mini *mini);
int		echo_cmd(char **tokens, t_mini *mini);
int		handle_append(char *s);
void	print_arg(char *str, int current, int flag, char **args);
int		check_flag(char *s);
void	ft_print_new_line(int flag_nl);
int		echo_cmd(char **tokens, t_mini *mini);
void	check_echo(t_mini *mini);
char	**new_args(char **s, int k, int k1);
int		check_pos_str(char **s);
char	**forming_echo_args(char **s, int i);
int		hanlde_redirects(t_mini *mini, char **s, int i);
int		deal_append(char *s, char *ss);
int		redirect_input(char *s);
int		redirect_output(char *s);
int		have_redi(char **s);
int		echo_len(char **s, int i);
char	**echo_w_red(char **s);
bool	is_a_builtin(t_mini *mini, int i);
int		free_struct_2(t_mini *mini, int i);
int		exit_check(t_mini *mini, int i);
void	update_path(t_mini *mini, int i);
char	*hndl_quotes(t_mini *mini, int i);
int		save_lines2(t_mini *mini, char *temp, int i);
char	**add_option(t_mini *mini, int i, char *temp);
void	delete_path(t_mini *mini);
int		create_child(t_mini *mini, int i, int flag, int j);
int		which_first(t_mini *mini, int i, int j, int flag);
void	create_flow(t_mini *mini);
void	exit_fork(t_mini *mini);
void	twenty_six_lines(t_mini *mini);
void	get_exit_status(t_mini *mini);
void	handle_execve(t_mini *mini, int i);
void	print_cmd(t_mini *mini, int i);
int		print(t_op op, char *ag);
int		create_pipes(t_mini *mini);
void	handle_pipes(t_mini *mini, int i, int flag);
void	close_pipes(t_mini *mini);
int		red_in(t_mini *mini);
int		count_red(t_mini *mini);
int		builtins2(t_mini *mini, int i);
bool	is_not_a_cmd(char *s, t_mini *mini);
bool	is_a_number(char *s);
void	sigint_on_child(int signal);
char	*get_expand(char *s);
char	*ft_before(char *s);
char	*ft_after(char *s);
int		qmark_and_dollar(char *str);
int		get_qmark(t_mini *mini, int i, char **str);
int		red_append(char **s, int i);
int		pipe_check(char **str);
void	ft_handle_eof(t_mini *mini);
void	ft_init_signals(void);
void	ft_ignore_signals(void);
void	ft_doc_signals(void);
t_mini	*return_mini(t_mini *newmini);
void	exit_heredoc(t_mini *mini);
void	signals_child(void);
int		ft_isaquote(char c);
int		get_grep(t_mini *mini, int i);
void	exit_fork3(t_mini *mini);
void	disp_pwd(t_mini *mini);
void	return_new_delimiter(char *delimiter, t_mini *mini);
int		var_exists(t_mini *mini, char *var);
void	handle_quotes(char **s);
int		red_out(t_mini *mini);
void	ft_init_signals(void);
int		handle_tokens(t_mini *mini);
void	parser(t_mini *mini);
int		check_spaces(char *s);
int		ft_var(char *str);
int		ft_before_exp(char *str);
char	*expand_str_hredoc(t_mini *mini, char **str);
void	free_expand2_heredoc(t_mini *mini, int flag, char *s);
int		get_qmark_heredoc(t_mini *mini, char **str);
int		exit_expand_heredoc(char *s, t_mini *mini);
void	do_all_heredoc(t_mini *mini, char *env, char **s);
int		quote_after_exp_hereodc(char *s);
void	ft_handle_sigint_ign(int sig);
void	ft_handle_sigint(int sig);
void	ft_handle_sigquit(int sig);
int		qmark_and_dollar(char *str);
void	ohhh_boy(char **str, int i);
void	free_expand2(t_mini *mini, int flag, int i, char **s);
int		quote_after_exp(char *s);
int		exit_expand(char *s, t_mini *mini);
void	do_all(t_mini *mini, int i, char *env, char **s);
int		qmark_and_dollar(char *str);
int		create_and_exit(char *str);
int		check_exit_arguments(char **s);
bool	ft_arrayisnum(char **str);
int		check_done(char **str, int i);
#endif
