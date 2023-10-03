/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leschenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 13:39:54 by leschenb          #+#    #+#             */
/*   Updated: 2022/12/05 13:39:57 by leschenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	size;

	size = 0;
	while (*s != '\0')
	{
		s++;
		size++;
	}
	while (size >= 0)
	{
		if (*s == (unsigned char)c)
		{
			return ((char *) s);
		}
		s--;
		size--;
	}
	return (NULL);
}
