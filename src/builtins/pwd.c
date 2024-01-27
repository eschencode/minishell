/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeastman <aeastman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:57:36 by leschenb          #+#    #+#             */
/*   Updated: 2024/01/27 11:29:36 by aeastman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	pwd_builtin(t_shell *shell, int fd_in, int fd_out)
{
	char	cwd[1024];

	ft_dup2(fd_in, fd_out);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	shell->exit_code = 0;
	return (true);
}

bool	clearwindow(int fd_in, int fd_out)
{
	ft_dup2(fd_in, fd_out);
	printf("\033[H\033[J");
	return (true);
}
