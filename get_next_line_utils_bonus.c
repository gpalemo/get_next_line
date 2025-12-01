/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmauley <cmauley@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:40:49 by cmauley           #+#    #+#             */
/*   Updated: 2025/12/01 16:43:19 by cmauley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	int				i;

	i = 0;
	d = (unsigned char *) dest;
	s = (unsigned char *) src;
	if (!src && !dest)
		return (dest);
	while (n)
	{
		d[i] = s[i];
		i++;
		n--;
	}
	return (dest);
}

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

char	*gnl_strjoin(char *s1, char const *s2)
{
	char	*str;
	int		len1;
	int		len2;

	len1 = 0;
	if (s1)
		len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (len2 == 0)
		return (s1);
	str = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!str)
	{
		free(s1);
		return (NULL);
	}
	if (s1)
	{
		ft_memcpy(str, s1, len1);
		free (s1);
	}
	ft_memcpy(str + len1, s2, len2 + 1);
	return (str);
}

char	*free_wrapper(char *str)
{
	if (str)
		free(str);
	return (NULL);
}

char	*setup_stash(int fd, char *stash)
{
	ssize_t		lu;
	char		*buff;
	int			nl_found;

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (free_wrapper(stash));
	lu = 1;
	nl_found = istherenl(stash);
	while (lu > 0 && !nl_found)
	{
		lu = read(fd, buff, BUFFER_SIZE);
		if (lu <= 0)
			break ;
		buff[lu] = '\0';
		stash = gnl_strjoin(stash, buff);
		if (!stash)
			return (free_wrapper(buff));
		if (istherenl(buff))
			nl_found = 1;
	}
	free(buff);
	if (lu < 0)
		return (free_wrapper(stash));
	return (stash);
}
