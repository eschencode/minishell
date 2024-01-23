/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeastman <aeastman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:45:13 by aeastman          #+#    #+#             */
/*   Updated: 2024/01/23 17:42:59 by aeastman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	env_init(t_shell *shell)
{
	int				y;
	int				len;
	extern	char 	**environ;

	len = 0;
	while (environ[len])
		len++;
	shell->env = malloc(sizeof(char *) * (len + 1));
	y = -1;
	while (environ[++y])
		shell->env[y] = ft_strdup(environ[y]);
	shell->env[y] = NULL;
}

int	eval_exit_loop(t_shell *shell, t_tokens *tokens)
{
	if (shell->input_str == NULL || \
	ft_strncmp(shell->input_str, "exit", ft_strlen("exit")) == 0 || \
	ft_strncmp(shell->input_str, "q", ft_strlen("q")) == 0)
	{
		ft_free_all(tokens, shell);
		shell->loop_exit = 1;
		return (1);
	}
	return (0);
}

int	validate_input_str(t_shell *shell)
{
	int		x;
	char	*str;

	str = shell->input_str;
	x = -1;
	while (str[++x])
	{
		if (str[x] != ' ' && str[x] != '\t')
			return (0);
	}
	return (1);
}

int	eval_input_error(t_shell *shell)
{
	if (shell->input_str[0] == '\0' \
	|| count_quotes(shell->input_str) % 2 != 0 \
	|| validate_input_str(shell) == 1)
	{
		free(shell->input_str);
		return (1);
	}
	return (0);
}

void	minishell_init(t_shell *shell)
{
	shell->tokens = NULL;
	rl_initialize();
	using_history();
	env_init(shell);
	shell->cd_last_path = NULL;
	shell->path = NULL;
	shell->exe_path = NULL;
	shell->exit_code = 0;
	add_path_to_hist(shell);
}

int	syntaxchecker_onlyretoken(t_shell *shell)
{
	if (shell->num_tokens == 1 && (shell->tokens[0].type == RIGHT || \
	shell->tokens[0].type == RIGHT_RIGHT || shell->tokens[0].type == LEFT || \
	shell->tokens[0].type == LEFT_LEFT))
	{
		printf ("syntax error\n");
		return(1);
	}
	else 
		return(0);
}

int	exit_check(t_shell *shell)
{
	int	i;

	i = 0;
	if (ft_strncmp(shell->input_str, "exit", ft_strlen("exit")) != 0)
		return (0);
	if (shell->num_tokens > 2)
	{
		printf("to many arguments for exit\n");
		return (1);
	}
	if (shell->num_tokens <= 1)
		exit(0);
	while (shell->tokens[1].token[i] != '\0')
	{
		if (!ft_isdigit(shell->tokens[1].token[i]))
		{
			printf("exit only takes numeric arguments\n");
			return (1);
		}
		i++;
	}
	exit(ft_atoi(shell->tokens[1].token));
	return (1);
}

void	minishell_loop(t_shell *shell)
{
	char prompt[6] = "msh$ ";
	shell->input_str = readline(prompt);
	if (eval_input_error(shell) == 0)
	{
		if (shell->tokens != NULL)
			ft_free_tokens(shell->tokens);
		add_history(shell->input_str);
		run_expanders(shell);
		tokenization(shell, shell->input_str);
		if (exit_check(shell) == 1)
			return;
		if (syntaxchecker_onlyretoken(shell) == 1)
			return;
		// print_tokens(shell->tokens);
		parser(shell);
		// print_clist(shell);
		executor(shell);
		ft_free_clist(shell);
		free(shell->input_str);
	}
}

int	main()
{
	t_shell shell;
	struct sigaction sa_int;
	struct sigaction sa_quit;
	shell.loop_exit = 0;

	sigs_init(&sa_int, &sa_quit);
	minishell_init(&shell);

	while (shell.loop_exit == 0)
		minishell_loop(&shell);
}
