/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanders.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeastman <aeastman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 11:01:27 by aeastman          #+#    #+#             */
/*   Updated: 2024/01/25 13:42:31 by aeastman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*trim_until_space(char *str)
{
	int		x;
	char	*trimmed;

	x = 0;
	while (str[x] && str[x] != ' ' && str[x] != '	' && \
	str[x] != '\"' && str[x] != '\'')
		x++;
	trimmed = malloc(sizeof(char) * (x + 1));
	ft_strlcpy(trimmed, str, x);
	return (trimmed);
}

char	*remove_bad_env(char *str, int len)
{
	int		beg;
	char	*new_str;

	beg = len;
	new_str = malloc(sizeof(char) * ft_strlen(str) + 1);
	len++;
	while (str[len] && str[len] != ' ' && str[len] != '\t')
		len++;
	ft_strlcpy(new_str, str, beg);
	new_str[beg] = '\0';
	ft_strcat(new_str, str + len);
	return (new_str);
}

void	value_inserter(t_shell *shell, int x)
{
	char	*var;
	char	*val;
	char	*new_str;

	var = trim_until_space(shell->input_str + x + 1);
	val = env_get_val(shell, var);
	if (val == NULL && ft_strcmp(var, "?") == 0)
		val = ft_itoa(shell->exit_code);
	if (val != NULL)
	{
		new_str = ret_push_val_into_str(shell->input_str, val, var, x);
		free(shell->input_str);
		shell->input_str = new_str;
	}
	if (val == NULL)
	{
		new_str = remove_bad_env(shell->input_str, x);
		free(shell->input_str);
		shell->input_str = new_str;
	}
	if (ft_strcmp(var, "?") == 0)
		free(val);
	free(var);
}

void	value_inserter_tilde(t_shell *shell, int x)
{
	char	*var;
	char	*val;
	char	*new_str;

	var = ft_strdup("~");
	val = env_get_val(shell, "HOME");
	if (val == NULL)
	{
		free(var);
		return ;
	}
	if (val != NULL)
	{
		new_str = ret_push_val_into_str_tilde(shell->input_str, val, var, x);
		free(shell->input_str);
		shell->input_str = new_str;
	}
	free(var);
}

void	expander_quotes(t_shell *shell)
{
	int	x;
	int	sq_mode;
	int	dq_mode;

	x = -1;
	dq_mode = 0;
	sq_mode = 0;
	while (shell->input_str[++x])
	{
		if (shell->input_str[x] == '\"' && dq_mode == 0)
			dq_mode = 1;
		else if (shell->input_str[x] == '\"' && dq_mode == 1)
			dq_mode = 0;
		if (shell->input_str[x] == '\'' && sq_mode == 0)
			sq_mode = 1;
		else if (shell->input_str[x] == '\'' && sq_mode == 1)
			sq_mode = 0;
		if (sq_mode != 1 && shell->input_str[x] == '$' && \
		dollar_check(shell->input_str + x) == 0)
			value_inserter(shell, x);
		if (sq_mode != 1 && shell->input_str[x] == '~')
			value_inserter_tilde(shell, x);
		if (x >= (int)ft_strlen(shell->input_str))
			return ;
	}
}
