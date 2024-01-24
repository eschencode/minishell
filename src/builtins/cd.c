/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leschenb <leschenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:02:41 by leschenb          #+#    #+#             */
/*   Updated: 2024/01/24 16:42:00 by leschenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	add_path_to_hist(t_shell *shell)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return ;
	if (shell->cd_last_path != NULL)
		free(shell->cd_last_path);
	shell->cd_last_path = malloc(sizeof(char) * (ft_strlen(cwd) + 1));
	ft_strcpy(shell->cd_last_path, cwd);
}

bool	cd_home(t_shell *shell, char *cmd)
{
	char	*path;

	if (cmd == NULL || ft_strcmp(cmd, "~") == 0)
	{
		path = env_get_val(shell, "HOME");
		if (path == NULL)
		{
			printf("cd: HOME not set\n");
			shell->exit_code = 1;
			return (true);
		}
		if (chdir(path) < 0)
		{
			printf("cd: No such file or directory: %s\n", path);
			shell->exit_code = 1;
		}
		return (true);
	}
	return (false);
}

bool	cd_last_path(t_shell *shell, char *cmd)
{
	char	*old_path;

	if (ft_strcmp(cmd, "-") == 0)
	{
		old_path = ft_strdup(shell->cd_last_path);
		add_path_to_hist(shell);
		printf("%s\n", old_path);
		chdir(old_path);
		free(old_path);
		return (true);
	}
	return (false);
}

bool	cd(t_shell *shell, char *cmd, int fd_in, int fd_out)
{
	char	*path;

	ft_dup2(fd_in, fd_out);
	path = cmd;
	if (cd_home(shell, cmd))
		return (true);
	if (cd_last_path(shell, cmd))
		return (true);
	add_path_to_hist(shell);
	if (chdir(path) < 0)
	{
		printf("cd: No such file or directory: %s\n", path);
		shell->exit_code = 1;
	}
	return (true);
}
