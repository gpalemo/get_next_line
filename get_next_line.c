/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmauley <cmauley@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 20:34:17 by cmauley           #+#    #+#             */
/*   Updated: 2025/11/07 17:10:24 by cmauley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*append_buffer(char *line, char *buffer)
{
	char	*tmp;
	
	if (!line)
		return (ft_strdup(buffer));
	else
	{
		tmp = ft_strjoin(line, buffer);
		free (line);
		return (tmp);
	}
	
}

static char	*fill_line_buffer(int fd, char *left_c, char *buffer)
{
	char	*line;
	int		b_read;

	line = NULL;
	if (left_c)
		line = ft_strdup(left_c);
	b_read = read(fd, buffer, BUFFER_SIZE);
	while (b_read > 0)
	{
		buffer[b_read] = '\0';
		line = append_buffer(line, buffer);
		if (!line || ft_strchr(line, '\n'))
			break ;
		b_read = read(fd, buffer, BUFFER_SIZE);
	}
	if (b_read < 0)
	{
		free(line);
		return (NULL);
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
	if (!line)
	{
		free (left_c);
		left_c = NULL;
		return (NULL);
	}
	free(left_c);
	left_c = set_line(line);
	return (line);
}
