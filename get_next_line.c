/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:48:04 by habouda           #+#    #+#             */
/*   Updated: 2024/05/30 01:19:17 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
/*# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>

size_t	ft_strlen(char const *str)
{
	size_t i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	int		i;
	int		j;

	dest = malloc (sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!dest)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		dest[i] = s2[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;

	i = 0;
	src_len = ft_strlen(src);
	if (!src || !dst)
		return (src_len);
	if (size <= 0)
		return (src_len);
	while (src[i] != '\0' && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}*/

char	*fill_line(char *stash)
{
	int		i;
	char	*line;

	i = 0;
	while (stash[i] != '\n' && stash[i])
		i++;
	line = malloc(sizeof(char) * i + 2); /*I +2 car 1 byute pour /n et 1 pour NULL*/
	if (!line)
		return (NULL);
	ft_strlcpy(line, stash, i + 2);
	return (line);
}

static	char	*clear_stash(char *stash)
{
	int		i;
	char	*new_stash;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\0') /*PERMET DE DIFFERENCIER LES CAS OU LA LIGNE TERMINE PAR /n et les fois ou non (ie toute derniere ligne)*/
	{
		new_stash = ft_strdup(&stash[i]);
		free (stash);
		stash = NULL;
		if (new_stash[0] == '\0')
		{
			free (new_stash);
			return (NULL);
		}
		return (new_stash);
	}
	else
	{
		new_stash = ft_strdup(&stash[i + 1]);  
		free (stash); /*important je faisait pas*/
		stash = NULL;
		return (new_stash);
	}
}

static char	*read_and_fill_stash(int fd, char *stash)
{
	ssize_t	bytes_read;
	char	*temp;
	char	*buffer;

	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			break ;
		buffer[bytes_read] = '\0'; /*bien penser a le faire sinon on va trop lire hihihihi (tuez moi)*/
		if (!stash)
			stash = ft_strdup("");
		temp = ft_strdup(stash);
		free (stash); /*free qui n'etais pas realiser donc memleaks KO 3eme test*/
		stash = ft_strjoin(temp, buffer);
		free (temp);
		temp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (free(buffer), stash);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	stash = read_and_fill_stash(fd, stash); 
	if (!stash || stash[0] == '\0') /*bien penser a stash[0] pour check les cas ou stash vide*/
	{
		free (stash);
		stash = NULL;
		return (NULL);
	}
	line = fill_line (stash);
	stash = clear_stash(stash);
	return (line);
}

/*int main(void)
{
	int fd;
	char *line;

	// Open the file test.txt in read-only mode
	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return (1);
	}

	// Read and display lines from the file until the end
	(line = get_next_line(fd));
	printf("%s", line);
	free(line);  // Free the memory allocated for the line
	(line = get_next_line(fd));
	printf("%s", line);
	free(line);  // Free the memory allocated for the line



	// Close the file
	close(fd);
	return (0);
}*/