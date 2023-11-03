#include "../../include/minishell.h"

int cd(t_shell shell)
{
	if(shell.input_str[0] == 'c' && shell.input_str[1] == 'd' && shell.input_str[2] == ' ')
		{
			shell.input_str[ft_strlen(shell.input_str)] = '\0';
			if(chdir(shell.input_str + 3) < 0)
				{
					printf("cant cd %s\n",shell.input_str +3);
					return(-1);
				}
		}
		return(0);
}

int pwd_builtin(t_shell shell)
{
	if(strcmp(&shell.tokens->token[0], "pwd") == 0)
			{
				char cwd[1024];
				if (getcwd(cwd, sizeof(cwd)) != NULL)
				{
					printf("%s\n", cwd);
				}
			}
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
