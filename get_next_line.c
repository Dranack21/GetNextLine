/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:48:04 by habouda           #+#    #+#             */
/*   Updated: 2024/05/27 17:10:54 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*realloc()
{
	
}

char	*get_next_line(int fd)
{
	int		bytes_read;
	char	buffer[42];
	char	*str;
	int		i;

	i = 0;
	if (fd < 0)
		return (NULL);
	bytes_read = read(fd, &buffer, 1);
	while (bytes_read > 0)
	{
		ft_putchar(buffer);
		if (buffer[i] = '\n')
			break;
		bytes_read = read(fd, &buffer, 1);
	}
	return (str);
}