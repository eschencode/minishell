/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leschenb <leschenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:46:53 by aeastman          #+#    #+#             */
/*   Updated: 2024/01/29 17:13:34 by leschenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	heredoc_create(void)
{
	int	fd;

	fd = open("src/heredoc/heredoc.txt", \
	O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
	return (fd);
}

void	print_clist(t_clist *head)
{
	t_clist	*temp;
	int		i;

	temp = head;
	while (temp != NULL) 
	{
		printf("Command: %s\n", temp->cmd[0]);	
		printf("Arguments: ");
		for (i = 1; i < temp->n_args; i++)
		{
			printf("%s ", temp->cmd[i]);
		}
		printf("\n");
		temp = temp->next;
	}
}
