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
