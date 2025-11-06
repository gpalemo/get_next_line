/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmauley <cmauley@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 20:34:17 by cmauley           #+#    #+#             */
/*   Updated: 2025/11/06 21:29:22 by cmauley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*fill_line_buffer(int fd, char *left_c, char *buffer)
{
	char	*line;
	char	*tmp;
	int		b_read;

	line = NULL;
	if (left_c != NULL)
		line = ft_strdup(left_c);
	b_read = read(fd, buffer, BUFFER_SIZE);
	while (b_read > 0)
	{
		buffer[b_read] = '\0';
		if (!line)
			line = ft_strdup(buffer);
		else
		{
			tmp = ft_strjoin(line, buffer);
			free (line);
			line = tmp;
		}
		if (!line || ft_strchr(line, '\n'))
			break ;
		b_read = read(fd, buffer, BUFFER_SIZE);
	}
	return (line);
}

static char	*set_line(char *line_buffer)
{
	char	*n;
	char	*new_left_c;
	int		i;

	if (!line_buffer)
		return (NULL);
	n = ft_strchr(line_buffer, '\n');
	if (!n)
		return (NULL);
	i = (n - line_buffer) + 1;
	if (line_buffer[i])
	{
		new_left_c = ft_strdup(line_buffer + i);
	}
	else
	{
		new_left_c = NULL;
	}
	line_buffer[i] = '\0';
	return (new_left_c);
}

char	*get_next_line(int fd)
{
	char			*buffer;
	char			*line;
	static char		*left_c;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	line = fill_line_buffer(fd, left_c, buffer);
	free (buffer);
	free (left_c);
	if (!line)
		left_c = NULL;
		free (left_c);
		return (NULL);
	left_c = set_line(line);
	return (line);
}
