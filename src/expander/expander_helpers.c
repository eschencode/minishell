/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leschenb <leschenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 13:57:14 by aeastman          #+#    #+#             */
/*   Updated: 2024/01/25 16:25:42 by leschenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// deprecated -> wanted to keep because kinda cute
void	get_rid_of_quotes(char *str)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (str[x])
	{
		if (str[x] != '\'' && str[x] != '\"')
		{
			str[y] = str[x];
			y++;
		}
		x++;
	}
	str[y] = '\0';
}

char	*ret_push_val_into_str_tilde(char *str, char *val, char *var, int pos)
{
	int		x;
	int		new_len;
	char	*new_str;

	new_len = ft_strlen(str) - ft_strlen(var) + ft_strlen(val);
	new_str = malloc(sizeof(char) * (new_len + 1));
	x = -1;
	while (++x < pos)
		new_str[x] = str[x];
	while (str[pos] && str[pos] == '~')
		pos++;
	new_str[x] = '\0';
	ft_strcat(new_str, val);
	x = x + ft_strlen(val);
	while (str[pos])
	{
		new_str[x] = str[pos];
		x++;
		pos++;
	}
	new_str[x] = '\0';
	return (new_str);
}

char	*ret_push_val_into_str(char *str, char *val, char *var, int pos)
{
	int		x;
	int		new_len;
	char	*new_str;

	x = -1;
	new_len = ft_strlen(str) - ft_strlen(var) + ft_strlen(val);
	new_str = malloc(sizeof(char) * (new_len + 1));
	while (++x < pos)
		new_str[x] = str[x];
	while (str[pos] && str[pos] != ' ' && str[pos] != '\"' && str[pos] != '\'')
		pos++;
	new_str[x] = '\0';
	ft_strcat(new_str, val);
	x = x + ft_strlen(val);
	while (str[pos])
	{
		new_str[x] = str[pos];
		x++;
		pos++;
	}
	new_str[x] = '\0';
	return (new_str);
}

int	dollar_check(char *str)
{
	if (ft_strlen(str) == 1)
		return (1);
	if (!((str[1] >= 'A' && str[1] <= 'Z') || \
	(str[1] >= 'a' && str[1] <= 'z') || str[1] == '_' || str[1] == '?'))
		return (1);
	return (0);
}
