/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeastman <aeastman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:35:56 by aeastman          #+#    #+#             */
/*   Updated: 2024/01/18 17:19:30 by aeastman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char *fast_forward_str(char *str)
{
	int x;

	x = 0;
	while (str[x] && (str[x] == ' ' || str[x] == '\t'))
		x++;
	return (str + x);
}

char **add_element(char **array, int current_size, char *new_element)
{

	if (array == NULL)
	{
		array = malloc(sizeof(char *) * 2);
		array[0] = new_element;
		array[1] = NULL;
	}
	
	array = realloc(array, (current_size + 1) * sizeof(char*));

	array[current_size] = new_element;

	return array;
}



int		get_regular_len(char *str)
{
	int len;

	len = 0;
	while (str[len] && str[len] != ' ' && str[len] != '\t')
		len++;
	printf("str \"%s\" len %d\n", str, len);
	return (len);
}

int		get_quotes_len(char *str)
{
	char c;
	int len;

	c = str[0];
	len = 1;
	while (str[len] && str[len] != c)
		len++;
	return (len);
}

char	*get_trim_str(char *str)
{
	int len;
	char *new_str;

	len = 0;
	if (str[0] == '\'' || str[0] == '\"')
		len = get_quotes_len(str);
	else
		len = get_regular_len(str);
	new_str = malloc(sizeof(char) * len + 2);
	strncpy(new_str, str, len);
	new_str[len] = '\0';
	return (new_str);
}


int		get_double_str_len(char **str)
{
	int y;

	if (str == NULL)
		return 0;
	y = 0;
	while (str[y])
		y++;
	
	return (y);
}

void	custom_split(char *str)
{
	char 	*test_str;
	char	**split;
	char	*trim_str;

	split = NULL;
	test_str = fast_forward_str(str);
	test_str = ft_strdup(test_str);
	while (*test_str)
	{
		trim_str = get_trim_str(fast_forward_str(test_str));
		split = add_element(split, get_double_str_len(split), trim_str);
		test_str += ft_strlen(trim_str);
	}
	free_double_str(split);
	free(split);
	free(test_str);
}