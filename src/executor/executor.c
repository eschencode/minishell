#include "../../include/minishell.h"


int execute_builtins(t_shell shell)
{
	pwd_builtin(shell);
	//echo(shell);
	//add rest of builtins here
}

int execute_externals(t_shell shell)
{
	pid_t child_pid;
	int child_status;

		//external clists
		if(child_pid == 0)
		{
			printf("pid %d\n",child_status);
		}
		if(execvp(shell.tokens->token[0],shell.clist->args) == -1)
		{
			printf("execvp error");
		}
		else if (child_pid > 0)
		{
		// This code is executed in the parent process

		// Wait for the child process to complete (optional)
			if (waitpid(child_pid, &child_status, 0) == -1)
			{
					perror("waitpid");
				exit(EXIT_FAILURE);
			}

		// Check the exit status of the child process
			if (WIFEXITED(child_status))
			{
				printf("Child process exited with status %d\n", WEXITSTATUS(child_status));
			}
			else if (WIFSIGNALED(child_status))
			{
				printf("Child process terminated by signal %d\n", WTERMSIG(child_status));
			}
			else
			{
				perror("fork");
				exit(EXIT_FAILURE);
			}
	return(0);
	}
}
// fork only for ./bla bla and builtins on parent
int executor(t_shell shell)
{
	//shell.clist->type = PATH;
	shell.clist->external_flag = false;
	if(shell.clist->external_flag == false)
	{
		execute_builtins(shell);
	}
	else if(shell.clist->external_flag == true)
	{
		execute_externals(shell);
	}
}
