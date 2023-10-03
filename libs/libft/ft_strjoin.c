/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leschenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 11:51:43 by leschenb          #+#    #+#             */
/*   Updated: 2022/12/08 11:51:45 by leschenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		l;
	char	*nstr;

	l = 0;
	i = 0;
	nstr = malloc (((ft_strlen ((char *)s1) + \
	ft_strlen ((char *)s2)) + 1) * sizeof(char));
	if (nstr == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		nstr[i] = s1[i];
		i++;
	}
	while (s2[l] != '\0')
	{
		nstr[i] = s2[l];
		l++;
		i++;
	}
	nstr[i] = '\0';
	return (nstr);
}
