/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeastman <aeastman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:35:56 by aeastman          #+#    #+#             */
/*   Updated: 2024/01/26 15:25:51 by aeastman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_trim_str(char *str)
{
	int		len;
	char	*new_str;

	if (ft_strcmp("\"\"", str) == 0 || ft_strcmp("\'\'", str) == 0)
		return (str);
	len = 0;
	if (str[0] == '\'' || str[0] == '\"')
		len = get_quotes_len(str);
	else
		len = get_regular_len(str);
	new_str = malloc(sizeof(char) * len + 2);
	ft_strlcpy(new_str, str, len);
	new_str[len] = '\0';
	return (new_str);
}

int	get_double_str_len(char **str)
{
	int	y;

	if (str == NULL)
		return (0);
	y = 0;
	while (str[y])
		y++;
	return (y);
}

void	get_rid_of_quotes_str(char *str)
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

void	remove_quotes_split(char **str)
{
	int	y;

	y = -1;
	while (str[++y])
	{
		if (ft_strchr(str[y], '\"') != NULL || ft_strchr(str[y], '\'') != NULL)
			get_rid_of_quotes_str(str[y]);
	}
}

char	**custom_split(char *str)
{
	char		*org_ptr;
	char		*test_str;
	char		*trim_str;
	char		**split;

	split = NULL;
	test_str = fast_forward_str(str);
	test_str = ft_strdup(test_str);
	org_ptr = test_str;
	while (*test_str)
	{
		trim_str = get_trim_str(test_str);
		if (ft_strcmp("\"\"", trim_str) != 0 && ft_strcmp("\'\'", trim_str) != 0)
			split = add_element(split, get_double_str_len(split), trim_str);
		test_str += ft_strlen(trim_str);
		test_str += fast_forward_str_int(test_str);
	}
	free(org_ptr);
	remove_quotes_split(split);
	return (split);
}
