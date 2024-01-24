/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeastman <aeastman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 11:34:11 by aeastman          #+#    #+#             */
/*   Updated: 2024/01/24 11:46:20 by aeastman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*fast_forward_str(char *str)
{
	int	x;

	x = 0;
	while (str[x] && (str[x] == ' ' || str[x] == '\t'))
		x++;
	return (str + x);
}

int	fast_forward_str_int(char *str)
{
	int	x;

	x = 0;
	while (str[x] && (str[x] == ' ' || str[x] == '\t'))
		x++;
	return (x);
}

char	**add_element(char **array, int current_size, char *new_element)
{
	if (array == NULL)
	{
		array = malloc(sizeof(char *) * 2);
		array[0] = new_element;
		array[1] = NULL;
		return (array);
	}
	array = realloc(array, (current_size + 2) * sizeof(char *));
	array[current_size] = new_element;
	array[current_size + 1] = NULL;
	return (array);
}

int	get_regular_len(char *str)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != ' ' && str[len] != '\t')
		len++;
	return (len);
}

int	get_quotes_len(char *str)
{
	char	c;
	int		len;

	c = str[0];
	len = 1;
	while (str[len] && str[len] != c)
		len++;
	if (str[len] == c)
		len++;
	return (len);
}
