#include "../../include/minishell.h"

bool cd(t_shell shell)
{
	if(shell.input_str[0] == 'c' && shell.input_str[1] == 'd' && shell.input_str[2] == ' ')
		{
			shell.input_str[ft_strlen(shell.input_str)] = '\0';
			if(chdir(shell.input_str + 3) < 0)
					printf("cant cd %s\n",shell.input_str +3);
		}
		return(true);
}

bool 	pwd_builtin(t_clist *cmd, int fd_in, int fd_out)
{
	
	if(strcmp(cmd->cmd[0], "pwd") == 0)
	{
		ft_dup2(fd_in, fd_out);
				char cwd[1024];
				if (getcwd(cwd, sizeof(cwd)) != NULL)
					printf("%s\n", cwd);
	}
	return (true);
}

int echo_l(t_shell shell)
{
	int i = 0;
	if(strcmp(&shell.tokens->token[0], "echo") == 0)
	{
		while(&shell.tokens->token[i])
			printf("%s",&shell.tokens->token[++i]);
	}
	return(0);
}


