/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmauley <cmauley@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:36:25 by cmauley           #+#    #+#             */
/*   Updated: 2025/12/01 16:49:26 by cmauley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	static char	*stash[MAX_FD];
	char		*line;

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	stash[fd] = setup_stash(fd, stash[fd]);
	if (!stash[fd] || *stash[fd] == '\0')
	{
		stash[fd] = free_wrapper(stash[fd]);
		return (NULL);
	}
	line = extract_line(stash[fd]);
	if (!line)
	{
		stash[fd] = free_wrapper(stash[fd]);
		return (NULL);
	}
	stash[fd] = cleanstash(stash[fd]);
	return (line);
}
