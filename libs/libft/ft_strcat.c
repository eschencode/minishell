/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeastman <aeastman@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 18:45:46 by aeastman          #+#    #+#             */
/*   Updated: 2023/11/26 18:47:48 by aeastman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


size_t	ft_strcat(char *dest, const char *src)
{
	size_t	i;
	size_t	destlen;
	size_t	srclen;
	size_t	start;

	i = -1;
	destlen = ft_strlen(dest);
	srclen = ft_strlen(src);
	start = destlen;
	while (src[++i])
		dest[start + i] = src[i];
	dest[start + i] = '\0';
	return (start + srclen);
}