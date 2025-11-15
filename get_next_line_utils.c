/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmauley <cmauley@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 16:13:25 by cmauley           #+#    #+#             */
/*   Updated: 2025/11/15 18:47:47 by cmauley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str && str[i])
	{
		i++;
	}
	return (i);
}

char	*gnl_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		len1;
	int		len2;
	int		i;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	i = 0;
	str = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!str)
		return (NULL);
	while (i < len1)
	{
		str[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < len2)
	{
		str[i + len1] = s2[i];
		i++;
	}
	str[i + len1] = '\0';
	free((void *)s1);
	return (str);
}

char	*free_wrapper(char *str)
{
	free(str);
	str = NULL;
	return (NULL);
}

char	*setup_stash(int fd, char *stash)
{
	ssize_t		lu;
	char		*buff;

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	lu = 1;
	while (lu > 0 && !istherenl(stash))
	{
		lu = read(fd, buff, BUFFER_SIZE);
		if (lu <= 0)
			break ;
		buff[lu] = '\0';
		stash = gnl_strjoin(stash, buff);
		if (!stash)
			return (free_wrapper(buff));
	}
	free(buff);
	if (lu < 0)
		return (free_wrapper(stash));
	if (!stash || *stash == '\0')
		return (free_wrapper(stash));
	return (stash);
}
