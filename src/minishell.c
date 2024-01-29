/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leschenb <leschenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:45:13 by aeastman          #+#    #+#             */
/*   Updated: 2024/01/29 17:14:38 by leschenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exit_routine(t_shell *shell, int exit_code)
{
	ft_free_all(shell->tokens, shell);
	shell->loop_exit = 1;
	exit(exit_code);
}

int	command_checker(t_shell *shell)
{
	if (shell->clist == NULL)
	{
		return (1);
	}
	return (0);
}

void	minishell_loop(t_shell *shell)
{
	char	prompt[6];

	ft_strlcpy(prompt, "msh$ ", 5);
	if (shell->buffer != NULL)
		free(shell->buffer);
	shell->buffer = readline(prompt);
	if (shell->buffer == NULL)
		exit_routine(shell, 0);
	shell->input_str = fast_forward_str(shell->buffer);
	if (eval_input_error(shell) == 0 && weird_token_catcher(shell) == 0)
	{
		if (shell->tokens != NULL)
			ft_free_tokens(shell->tokens);
		add_history(shell->input_str);
		expander_quotes(shell);
		tokenization(shell, shell->input_str);
		if (exit_check(shell) == 1)
			return ;
		parser(shell);
		executor(shell);
		ft_free_clist(shell);
	}
}

void	minishell_init(t_shell *shell)
{
	shell->tokens = NULL;
	shell->buffer = NULL;
	rl_initialize();
	using_history();
	env_init(shell);
	shell->cd_last_path = NULL;
	shell->input_str = NULL;
	shell->path = NULL;
	shell->exe_path = NULL;
	shell->exit_code = 0;
	add_path_to_hist(shell);
}

int	main(void)
{
	t_shell				shell;

	shell.loop_exit = 0;
	sigs_init();
	minishell_init(&shell);
	while (shell.loop_exit == 0)
		minishell_loop(&shell);
}
