/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redirections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leschenb <leschenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 11:41:15 by leschenb          #+#    #+#             */
/*   Updated: 2023/11/22 11:41:16 by leschenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

/*
>: Redirects standard output to a file, overwriting its contents if the file exists
>>: Appends standard output to a file, preserving existing content and adding new output at the end of the file.
<: Redirects standard input to come from a file rather than from the keyboard*/

bool check_for_redirections(t_shell *shell, t_clist *cmd)
{
	int i = 0;
	int fd;
	while(shell->tokens[i].token )
	{
		if(strcmp(shell->tokens[i].token, cmd->cmd[0]) == 0)
		{
			if (shell->tokens[i].type == RIGHT)
			{
				printf("RIGHT token[%d]=%s\n",i,shell->tokens[i].token);
				return(true);
			}
			else if(shell->tokens[i + 1].type == LEFT)
			{
				printf(" LEFT token[%d]=%s\n file to open = %s\n",i,shell->tokens[i].token, shell->tokens[i +2].token);
				fd = open(shell->tokens[i + 2].token, O_RDONLY);
				if(fd == -1)
				{
					printf("error opening file:%s",shell->tokens[i + 2].token);
					close(fd);
				}
				dup2(fd,STDIN_FILENO);
				close(fd);
				return(true);
			}
			if(shell->tokens[i].type == RIGHT_RIGHT)
			{
				printf("RIGHT_RIGHT token[%d]=%s\n",i,shell->tokens[i].token);
				
				return(true);
			}
		}
		i++;
		}
	return(false);
}

int redirect(t_shell shell)
{
	
}