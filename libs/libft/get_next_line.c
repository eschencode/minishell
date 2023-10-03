/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leschenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:02:47 by leschenb          #+#    #+#             */
/*   Updated: 2023/02/01 14:02:50 by leschenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdio.h>

int	ft_empty(char *left_str, char *buff)
{
	if (left_str[0] == '\0' && buff[0] == '\0')
	{
		free(left_str);
		free(buff);
		return (1);
	}
	else
		return (0);
}

char	*read2left_str(int fd, char *left_str)
{
	char	*buff;
	int		readbytes;

	readbytes = 1;
	buff = malloc ((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	while (!ft_strchr(left_str, '\n') && readbytes != 0)
	{
		readbytes = read (fd, buff, BUFFER_SIZE);
		if (readbytes == -1)
		{
			free(buff);
			free(left_str);
			return (NULL);
		}
		buff[readbytes] = '\0';
		left_str = ft_strjoin(left_str, buff);
		if (ft_empty(left_str, buff) == 1)
			return (NULL);
	}
	free(buff);
	return (left_str);
}

char	*ft_get_ret_str(char *left_str)
{
	int		i;
	char	*ret_str;

	i = 0;
	if (!left_str)
		return (NULL);
	while (left_str[i] && left_str[i] != '\n')
		i++;
	ret_str = (char *)malloc(sizeof(char) * (i + 2));
	if (!ret_str)
		return (NULL);
	i = 0;
	while (left_str[i] && left_str[i] != '\n')
	{
		ret_str[i] = left_str[i];
		i++;
	}
	if (left_str[i] == '\n')
	{
		ret_str[i] = left_str[i];
		i++;
	}
	ret_str[i] = '\0';
	return (ret_str);
}

char	*ft_new_left_str(char *left_str)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	while (left_str[i] != '\0' && left_str[i] != '\n')
		i++;
	if (!left_str[i])
	{
		free (left_str);
		return (NULL);
	}
	str = (char *) malloc(sizeof(char) * (ft_strlen (left_str) - i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (left_str[i])
		str[j++] = left_str[i++];
	str[j] = '\0';
	free(left_str);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*left_str;
	char		*ret_str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	left_str = read2left_str(fd, left_str);
	if (left_str == NULL)
	{
		return (NULL);
	}
	ret_str = ft_get_ret_str(left_str);
	left_str = ft_new_left_str(left_str);
	return (ret_str);
}
