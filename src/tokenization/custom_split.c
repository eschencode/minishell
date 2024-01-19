/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeastman <aeastman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:35:56 by aeastman          #+#    #+#             */
/*   Updated: 2024/01/19 12:53:58 by aeastman         ###   ########.fr       */
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

int fast_forward_str_int(char *str)
{
	int x;

	x = 0;
	while (str[x] && (str[x] == ' ' || str[x] == '\t'))
		x++;
	return (x);
}

char **add_element(char **array, int current_size, char *new_element)
{
	if (array == NULL)
	{
		array = malloc(sizeof(char *) * 2);
		array[0] = new_element;
		array[1] = NULL;
		return (array);
	}
	array = realloc(array, (current_size + 2) * sizeof(char*));
	array[current_size] = new_element;
	array[current_size + 1] = NULL;
	return (array);
}

int		get_regular_len(char *str)
{
	int len;

	len = 0;
	while (str[len] && str[len] != ' ' && str[len] != '\t')
		len++;
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
	if (str[len] == c)
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

void print_double_str(char **str)
{
	int y;


	y = -1;
	printf("---DOUBLESTR---\n");
	while (str[++y])
		printf("%s\n", str[y]);
}

char **custom_split(char *str)
{
	char	**split;
	char	*org_ptr;
	char 	*test_str;
	char	*trim_str;

	split = NULL;
	test_str = fast_forward_str(str);
	test_str = strdup(test_str);
	org_ptr = test_str;
	while (*test_str)
	{
		trim_str = get_trim_str(test_str);
		split = add_element(split, get_double_str_len(split), trim_str);
		test_str += ft_strlen(trim_str);
		test_str += fast_forward_str_int(test_str);
	}
	free(org_ptr);
	return (split);
}