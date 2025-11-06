/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmauley <cmauley@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 20:34:17 by cmauley           #+#    #+#             */
/*   Updated: 2025/11/06 01:38:32 by cmauley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*static char	*fill_line_buffer(int fd, char *left_c, char *buffer)
{
	
}

static char	*set_line(char *line_buffer)
{
	
}*/

char	*get_next_line(int fd)
{
	char	*buffer;
	char	*line;
	int		b_read;
	char	*tmp;
	char	*n;
	int		len;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	line = NULL;
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
		if (!line)
			break;
		if (ft_strchr(line, '\n'))
			break ;
		b_read = read(fd, buffer, BUFFER_SIZE);
	}
	free (buffer);
	if (!line)
		return (NULL);
	n = ft_strchr(line, '\n');
	if (n)
	{
		len = (n - line) + 1;
		tmp = ft_substr(line, 0, len);
		free (line);
		line = tmp;
	}
	return (line);
}