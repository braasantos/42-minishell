#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../includes/LIBFT/libft.h"

typedef enum 	e_op
{
	COMMAND_NOT_FOUND,
}				t_op;

typedef struct s_mini
{
	char	*cmd;
	char	**newenvp;
}		t_mini;


#endif