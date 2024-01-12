#include "../../include/minishell.h"

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
	char *old_path;

	ft_dup2(fd_in, fd_out);
	path = cmd;
	if (cmd == NULL || strcmp(cmd, "~") == 0)
	{
		path = env_get_val(shell, "HOME");
		if (path == NULL)
		{
			printf("cd: HOME not set\n");
			shell->exit_code = 1;
			return (true);
		}
		if(chdir(path) < 0)
		{
			printf("cd: No such file or directory: %s\n", path);
			shell->exit_code = 1;
		}
		return (true);
		
	}
	if (strcmp(cmd, "-") == 0)
	{
		old_path = ft_strdup(shell->cd_last_path);
		add_path_to_hist(shell);
		printf("%s\n", old_path);
		chdir(old_path);
		free(old_path);
		return(true);
	}
	add_path_to_hist(shell);
	if(chdir(path) < 0)
	{
		printf("cd: No such file or directory: %s\n", path);
		shell->exit_code = 1;
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


