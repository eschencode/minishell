/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leschenb <leschenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 14:56:32 by leschenb          #+#    #+#             */
/*   Updated: 2024/01/23 15:04:33 by leschenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*create_exe_path(char *path, char *exe)
{
	char	*exe_path;

	exe_path = malloc(sizeof(char) * (ft_strlen(path) + ft_strlen(exe) + 4));
	ft_strlcpy(exe_path, path, ft_strlen(path));
	ft_strcat(exe_path, "/");
	ft_strcat(exe_path, exe);
	return (exe_path);
}

void	free_resources(t_shell *shell, char **paths)
{
	free_double_str(paths);
	free(paths);
	if (shell->exe_path)
		free(shell->exe_path);
}

void	set_exe_path(t_shell *shell, char *exe_path, char **paths)
{
	free_resources(shell, paths);
	shell->exe_path = exe_path;
}

void	exe_path(t_shell *shell, char *exe)
{
	int		y;
	char	*path;
	char	*exe_path;
	char	**paths;

	path = env_get_val(shell, "PATH");
	if (path == NULL)
	{
		shell->exe_path = NULL;
		return ;
	}
	paths = ft_split(path, ':');
	y = -1;
	while (paths[++y])
	{
		exe_path = create_exe_path(paths[y], exe);
		if (access(exe_path, F_OK | X_OK) == 0)
		{
			set_exe_path(shell, exe_path, paths);
			return ;
		}
		free(exe_path);
	}
	free_resources(shell, paths);
	shell->exe_path = NULL;
}
