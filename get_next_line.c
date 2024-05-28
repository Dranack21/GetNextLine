/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:48:04 by habouda           #+#    #+#             */
/*   Updated: 2024/05/28 15:44:26 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

void	*ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = '\0';
		i++;
	}
	return (s);
}

char	*ft_strdup(const char *source)
{
	int		i;
	char	*buffer;

	i = strlen(source);
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

int	check_stash(char *stash)
{
	int	i;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i] && stash[i] != '\n')
		return (0);
	else 
		return (i);
}

static 	char	*line_cutter(char *stash)
{
	int		i;
	int		k;
	char	*new;

	k = 0;
	i = 0;
	while (stash[i] && stash[i] !=  '\n')
		i++;
	new = malloc(sizeof(char) * i + 1);
	while (k < i && stash[k])
	{
		new[k] = stash[k];
		k++;
	}
	new[k] = '\0';
	return (new);
}

char	*ft_strjoin(char const *old, char const *new)
{
	char	*dest;
	int		i;
	int		j;

	dest = malloc (sizeof(char) * (strlen(old) + strlen(new) + 1));
	if (!dest)
		return (NULL);
	i = 0;
	j = 0;
	while (old[i])
	{
		dest[i] = old[i];
		i++;
	}
	while (new[j])
	{
		dest[i] = new[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*get_next_line(int fd)
{
	int		bytes_read;
	char	buffer[BUFFER_SIZE + 1];
	char	*line;
	static	char *stash;

	if (fd < 0 )
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	buffer[bytes_read] = '\0';
	if (!stash)
		stash = ft_strdup(buffer);
	if (check_stash(stash) == 0)
	{
		ft_bzero(buffer, BUFFER_SIZE);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		line = ft_strdup(buffer);
		stash = ft_strjoin(stash, line);
		free (line);
	}
	line = line_cutter(stash);
	if (!stash)
		return (NULL);
	stash = stash + strlen(line) + 1;
	return (line);
}


#include "get_next_line.h"
int main(void)
{
    int fd;
    char *line;

    // Ouvrir le fichier test.txt en lecture seule
    fd = open("test.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        return (1);
    }

    // Lire et afficher les lignes du fichier jusqu'à la fin
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s\n", line);
        free(line);  // Libérer la mémoire allouée pour la ligne
    }

    // Fermer le fichier
    close(fd);
    return (0);
}


