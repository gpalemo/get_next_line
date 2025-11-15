/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmauley <cmauley@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 18:45:08 by cmauley           #+#    #+#             */
/*   Updated: 2025/11/15 18:45:11 by cmauley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	istherenl(char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static size_t	line_len(char *stash)
{
	size_t	len;

	if (!stash)
		return (0);
	len = 0;
	while (stash[len] && stash[len] != '\n')
		len++;
	if (stash[len] == '\n')
		len++;
	return (len);
}

static char	*extract_line(char *stash)
{
	size_t	len;
	size_t	i;
	char	*line;

	len = line_len(stash);
	if (len == 0)
		return (NULL);
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (i < len)
	{
		line[i] = stash[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*cleanstash(char *stash)
{
	size_t	start;
	size_t	i;
	size_t	total;
	char	*temp;

	if (!stash)
		return (NULL);
	start = line_len(stash);
	total = ft_strlen(stash);
	if (start >= total)
		return (free_wrapper(stash));
	temp = malloc(total - start + 1);
	if (!temp)
		return (free_wrapper(stash));
	i = 0;
	while (stash[start + i])
	{
		temp[i] = stash[start + i];
		i++;
	}
	temp[i] = '\0';
	free(stash);
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = setup_stash(fd, stash);
	if (!stash || *stash == '\0')
		return (free_wrapper(stash));
	line = extract_line(stash);
	if (!line)
		return (free_wrapper(stash));
	stash = cleanstash(stash);
	return (line);
}
