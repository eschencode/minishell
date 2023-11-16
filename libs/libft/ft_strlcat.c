/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leschenb <leschenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 13:35:22 by leschenb          #+#    #+#             */
/*   Updated: 2023/11/15 13:15:06 by leschenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	ldst;
	size_t	lsrc;
	size_t	i;
	size_t	start;

	i = 0;
	lsrc = ft_strlen(src);
	ldst = ft_strlen(dst);
	if (size <= ldst)
		start = size;
	else
	{
		start = ldst;
		while ((start + i) < (size - 1) && src[i] != '\0')
		{
			dst[ldst + i] = src[i];
			i++;
		}
		dst[ldst + i] = '\0';
	}
	return (start + lsrc);
}
