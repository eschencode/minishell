/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leschenb <leschenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:46:53 by aeastman          #+#    #+#             */
/*   Updated: 2024/01/30 12:46:24 by leschenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	heredoc_create(void)
{
	int	fd;

	fd = open("heredoc.txt", \
	O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
	return (fd);
}
