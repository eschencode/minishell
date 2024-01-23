/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leschenb <leschenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:57:36 by leschenb          #+#    #+#             */
/*   Updated: 2024/01/23 17:09:46 by leschenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	pwd_builtin(int fd_in, int fd_out)
{
	char	cwd[1024];

	ft_dup2(fd_in, fd_out);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	return (true);
}

bool	clearwindow(int fd_in, int fd_out)
{
	ft_dup2(fd_in, fd_out);
	printf("\033[H\033[J");
	return (true);
}
