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

void	add_path_to_hist(t_shell *shell)
{
	char cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return ;
	if (shell->cd_last_path != NULL)
		free(shell->cd_last_path);
	shell->cd_last_path = malloc(sizeof(char) * (ft_strlen(cwd) + 1));
	strcpy(shell->cd_last_path, cwd);
}

bool	cd(t_shell *shell, char *cmd, int fd_in, int fd_out)
{
	char *path;

	ft_dup2(fd_in, fd_out);
	path = cmd;
	if (cmd == NULL || strcmp(cmd, "~") == 0)
		path = env_get_val(shell, "HOME");
	if (strcmp(cmd, "-") == 0)
	{
		path = shell->cd_last_path;
		printf("%s\n", path);
	}
	// check for tilde and substitute
	if (path == NULL)
		printf("CD: HOME not set, EXIT 1\n");
	if (path != NULL)
	{
		add_path_to_hist(shell);
		if(chdir(path) < 0)
			printf("CD: No such file or directory: %s, EXIT 1\n", path);
	}
	return(true);
}

bool 	pwd_builtin(int fd_in, int fd_out)
{
	ft_dup2(fd_in, fd_out);
	char cwd[1024];
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	return (true);
}


