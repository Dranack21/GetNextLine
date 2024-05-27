/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_lines_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:36:11 by habouda           #+#    #+#             */
/*   Updated: 2024/05/27 16:47:18 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

char	*ft_strdup(const char *source)
{
	int		i;
	char	*buffer;

	i = ft_strlen(source);
	buffer = malloc(i * sizeof(char) + 1);
	if (!buffer)
		return (NULL);
	i = 0;
	while (source[i])
	{
		buffer[i] = source[i];
		i++;
	}
	buffer[i] = '\0';
	return (buffer);
}