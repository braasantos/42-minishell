#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

typedef struct s_mini {
    char *args[100];
    char *newenvp[100];
    char *cmd1[100];
    int end[2];
    pid_t child1;
    pid_t child2;
} t_mini;


void ft_child1(t_mini *mini) {
    close(mini->end[0]); // Close read end of pipe
    dup2(mini->end[1], STDOUT_FILENO); // Redirect stdout to the pipe
    close(mini->end[1]); // Close duplicated write end of pipe
    if (execve(mini->cmd1[0], mini->args, mini->newenvp) == -1) {
        perror("execve");
        exit(EXIT_FAILURE);
    }
}

void ft_child2(t_mini *mini) {
    dup2(mini->end[0], STDIN_FILENO); // Redirect stdin to the pipe
    close(mini->end[0]); // Close duplicated read end of pipe
    close(mini->end[1]); // Close write end of pipe
    if (execve(mini->cmd1[2], mini->args, mini->newenvp) == -1) {
        perror("execve");
        exit(EXIT_FAILURE);
    }
}

void second_c(t_mini *mini)
{
	mini->child2 = fork();
	if (mini->child2 == 0)
	{
		// if (i == (count))
		ft_child2(mini);
	}
	else
		waitpid(-1, NULL, 0);
}

void exec_pipes(t_mini *mini) {
	int i = 0;
	while(i < 1)
	{
		pipe(mini->end); // Create pipe
		mini->child1 = fork();
		if (mini->child1 == 0)
			ft_child1(mini);
		else
		{
			second_c(mini);
		}
		close(mini->end[0]);
		close(mini->end[1]);
		waitpid(mini->child1, NULL, 0);
		waitpid(mini->child2, NULL, 0);
		i++;
	}
}

int main() {
    t_mini mini;
    mini.args[0] = "ls";
    mini.args[1] = NULL;
    mini.newenvp[0] = NULL;
    mini.cmd1[0] = "/bin/ls";
    mini.cmd1[2] = "/usr/bin/wc";
    exec_pipes(&mini);
    return 0;
}
