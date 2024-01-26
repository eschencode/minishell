/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_helpers_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeastman <aeastman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:43:45 by aeastman          #+#    #+#             */
/*   Updated: 2024/01/26 15:03:15 by aeastman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	if (str[0] == c && str[1] == c)
		return (2);
	len = 1;
	while (str[len] && str[len] != c)
		len++;
	if (str[len] == c)
		len++;
	return (len);
}
