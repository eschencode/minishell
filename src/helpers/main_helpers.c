/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeastman <aeastman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 19:05:57 by aeastman          #+#    #+#             */
/*   Updated: 2024/01/23 19:15:00 by aeastman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"


void	env_init(t_shell *shell)
{
	int				y;
	int				len;
	extern char		**environ;

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


int	weird_token_catcher(t_shell *shell)
{
	int		x;
	char	*str;

	x = 0;
	str = shell->input_str;
	while (str[x] && (str[x] == '<' || str[x] == '>' || str[x] == ' ' \
	|| str[x] == '|' || str[x] == '!'))
		x++;
	if ((int)ft_strlen(str) != x)
		return (0);
	free(shell->input_str);
	printf("syntax error: thats some weird ass input\n");
	return (1);
}

int	check_str_digit(char *str)
{
	int	x;

	x = -1;
	while (str[++x])
	{
		if (!ft_isdigit(str[x]))
		{
			printf("exit only takes numeric arguments\n");
			return (1);
		}
	}
	return (0);
}