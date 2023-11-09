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

		child_pid = fork();
		//external clists
	if (child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (child_pid == 0)
	{
		// This code is executed in the child process
		char *command = shell.clist->cmd;  // Assuming shell.clist->cmd contains the parsed path
        char *args[] = {shell.clist->cmd,shell.clist->args, NULL};  // You can modify this for additional arguments
		char *env[] = {NULL};

		// The execvp function is used to replace the current process
		// with a new process specified by the given executable file
		if (execve(command,args,env) == -1)                   //execvp("/Users/linuseschenbach/Desktop/minishell/test", NULL) == -1)
		{
			perror("exec error");
			exit(EXIT_FAILURE);
		}
	}
	else
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
	}

	return 0;
}

bool check_if_builtin(t_shell shell)
{
	int i = 0;
	if(strcmp(&shell.tokens->token[0], "pwd") == 0)
		return(true);
	else if (strcmp(&shell.tokens->token[0], "cd") == 0)
		return(true);
	else
	{
		return(false);
	}
}

// fork only for ./bla bla and builtins on parent
int executor(t_shell shell)
{
	//shell.clist->type = PATH;
		if(check_if_builtin(shell) == true)
			execute_builtins(shell);
		else
		{
			execute_externals(shell);
		}
			return(0);
}
