#include "../inc/minishell.h"

void parsing(t_mini *mini, char *str)
{
	new_string(str, mini);
	mini->args = ft_split(mini->new_str, ' ');
	if (mini->args[0] == NULL)
		return;
	if (ft_strchr(mini->args[0], '/'))
		mini->cmd = ft_strdup(mini->args[0]);
	else
		mini->cmd = ft_add(mini->newenvp, mini->new_str);
	if (ft_strcmp(mini->args[0], "cd") == 0)
		get_cd(mini->args[1]);
	else if (ft_strcmp(mini->args[0], "exit") == 0)
		exit(0);
	else
	{
	    mini->newpro = fork();
	    if (mini->newpro == 0)
		{
	        if (!mini->cmd)
	            print(COMMAND_NOT_FOUND, mini->args[0]);
	        if (execve(mini->cmd, mini->args, mini->newenvp) == -1)
	            exit(EXIT_FAILURE);
	 	}
	     else
	         waitpid(-1, NULL, 0);
	}
}