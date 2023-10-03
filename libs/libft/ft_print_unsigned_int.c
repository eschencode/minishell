/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned_int.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leschenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:15:46 by leschenb          #+#    #+#             */
/*   Updated: 2023/01/19 14:15:49 by leschenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_len(unsigned int nbr)
{
	int	i;

	i = 0;
	while (nbr != 0)
	{
		i++;
		nbr = nbr / 10;
	}
	return (i);
}

char	*ft_unsigned_itoa(int len, unsigned int nbr)
{
	char	*str;

	str = malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (0);
	str[len] = '\0';
	len--;
	while (nbr != 0)
	{
		str[len] = (nbr % 10) + '0';
		nbr = nbr / 10;
		len--;
	}
	return (str);
}

int	ft_print_unsigned_int(unsigned int nbr)
{
	int		len;
	char	*str;

	if (nbr == 0)
	{
		write(1, "0", 1);
		return (1);
	}
	else
	{
		len = ft_count_len(nbr);
		str = ft_unsigned_itoa(len, nbr);
		len = ft_print_str(str);
		free(str);
		return (len);
	}
}
