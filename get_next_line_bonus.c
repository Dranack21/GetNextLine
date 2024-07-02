/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habouda <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:48:04 by habouda           #+#    #+#             */
/*   Updated: 2024/07/02 17:29:54 by habouda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*fill_line(char *stash)
{
	int		i;
	char	*line;

	i = 0;
	while (stash[i] != '\n' && stash[i])
		i++;
	line = malloc(sizeof(char) * i + 2);
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
	if (stash[i] == '\0')
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
		free (stash);
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
		buffer[bytes_read] = '\0';
		if (!stash)
			stash = ft_strdup("");
		temp = ft_strdup(stash);
		free (stash);
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
	static char	*stash[1024];

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	stash[fd] = read_and_fill_stash(fd, stash[fd]);
	if (!stash[fd] || stash[fd][0] == '\0')
	{
		free (stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	line = fill_line (stash[fd]);
	stash[fd] = clear_stash(stash[fd]);
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