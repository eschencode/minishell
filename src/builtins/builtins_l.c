#include "../../include/minishell.h"

bool first_cd(t_shell shell)
{
	if(shell.input_str[0] == 'c' && shell.input_str[1] == 'd' && shell.input_str[2] == ' ')
		{
			shell.input_str[ft_strlen(shell.input_str)] = '\0';
			if(chdir(shell.input_str + 3) < 0)
					printf("cant cd %s\n",shell.input_str +3);
		}
		return(true);
}

bool cd(t_shell *shell, char *cmd, int fd_in, int fd_out)
{
	char *path;

	ft_dup2(fd_in, fd_out);
	path = cmd;
	if (cmd == NULL || strcmp(cmd, "~") == 0)
		path = env_get_val(shell, "HOME");
	if(chdir(path) < 0)
		printf("cant cd %s\n", path);
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


