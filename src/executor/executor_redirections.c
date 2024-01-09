/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_redirections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeastman <aeastman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 11:41:15 by leschenb          #+#    #+#             */
/*   Updated: 2024/01/09 10:06:56 by aeastman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

/*
>: Redirects standard output to a file, overwriting its contents if the file exists
>>: Appends standard output to a file, preserving existing content and adding new output at the end of the file.
<: Redirects standard input to come from a file rather than from the keyboard*/

bool check_for_redirections_out(t_shell *shell, t_clist *cmd)
{
	int i;

	i = 0;
	
	// added for memory safety
	if (strstr(shell->input_str, ">>") == NULL && strstr(shell->input_str, ">") == NULL && strstr(shell->input_str, "<") == NULL)
		return (false);

	while(shell->tokens[i].token && (strcmp(shell->tokens[i].token, cmd->cmd[0]) != 0))
		i++;
	i++;
	if(shell->tokens[i].token[0] == '-') //skips options
		i++;
	if (shell->tokens[i].type == RIGHT)
		shell->redirect_out = open(shell->tokens[i + 1].token, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	else if(shell->tokens[i + 2].type == RIGHT)
		shell->redirect_out = open(shell->tokens[i + 3].token, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if(shell->tokens[i].type == RIGHT_RIGHT)
		shell->redirect_out = open(shell->tokens[i + 1].token,  O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	else if(shell->tokens[i + 2].type == RIGHT_RIGHT)
		shell->redirect_out = open(shell->tokens[i + 3].token,  O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	if(shell->tokens[i].type == LEFT)//add check if out and in check for more tokens
		shell->redirect_in = open(shell->tokens[i + 1].token, O_RDONLY);
	else if(shell->tokens[i + 2].type == LEFT) //add check if out and in check for more tokens
		shell->redirect_in = open(shell->tokens[i + 3].token, O_RDONLY);
	return(false);
}
