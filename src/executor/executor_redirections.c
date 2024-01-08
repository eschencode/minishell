/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redirections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeastman <aeastman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 11:41:15 by leschenb          #+#    #+#             */
/*   Updated: 2024/01/05 20:37:59 by aeastman         ###   ########.fr       */
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
	int fd = -1;

  if (shell->num_tokens <= 1)
		return (false);

	while(shell->tokens[i].token && (strcmp(shell->tokens[i].token, cmd->cmd[0]) != 0))
	{
		i++;
	}
		if (shell->tokens[i + 1].type == RIGHT)
		{
			fd = open(shell->tokens[i + 2].token, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
			if(fd == -1)
			{
				printf("error opening file:%s",shell->tokens[i + 2].token);
				close(fd);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if(shell->tokens[i + 3].type == RIGHT)
		{
			fd = open(shell->tokens[i + 4].token, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
			if(fd == -1)
			{
				printf("error opening file:%s",shell->tokens[i + 2].token);
				close(fd);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		if(shell->tokens[i + 1].type == LEFT)//add check if out and in check for more tokens
		{
			fd = open(shell->tokens[i + 2].token, O_RDONLY);
			if(fd == -1)
			{
				printf("error opening file:%s",shell->tokens[i + 2].token);
				close(fd);
			}
			dup2(fd,STDIN_FILENO);
			close(fd);
		}
		else if(shell->tokens[i + 3].type == LEFT)//add check if out and in check for more tokens
		{
			fd = open(shell->tokens[i + 4].token, O_RDONLY);
			if(fd == -1)
			{
				printf("error opening file:%s",shell->tokens[i + 4].token);
				close(fd);
			}
			dup2(fd,STDIN_FILENO);
			close(fd);
		}
		if(shell->tokens[i + 1].type == RIGHT_RIGHT)
		{
			fd = open(shell->tokens[i + 2].token, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
			dup2(fd,STDOUT_FILENO);
			close(fd);
		}
		else if(shell->tokens[i + 3].type == RIGHT_RIGHT)
		{
			fd = open(shell->tokens[i + 4].token, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
			dup2(fd,STDOUT_FILENO);
			close(fd);
		}

	return(false);
}
/*

pipe
cmd < in + > out | second cmd

*/
