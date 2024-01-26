/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeastman <aeastman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 11:34:11 by aeastman          #+#    #+#             */
/*   Updated: 2024/01/26 14:45:13 by aeastman         ###   ########.fr       */
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

void	duplicate_str_arr(char **new_arr, char **old_str)
{
	int	y;

	y = -1;
	while (old_str[++y])
		new_arr[y] = ft_strdup(old_str[y]);
}

char	**ft_realloc_array(char **ptr, size_t newsize)
{
	char	**new_array;

	new_array = malloc(sizeof(char **) * newsize);
	duplicate_str_arr(new_array, ptr);
	free_double_str(ptr);
	free(ptr);
	return (new_array);
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
	array = ft_realloc_array(array, (current_size + 2) * sizeof(char *));
	array[current_size] = new_element;
	array[current_size + 1] = NULL;
	return (array);
}
