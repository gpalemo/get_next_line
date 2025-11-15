/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmauley <cmauley@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 16:13:36 by cmauley           #+#    #+#             */
/*   Updated: 2025/11/15 18:29:24 by cmauley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# include <stdlib.h> // malloc, free
# include <unistd.h> // read, close

char	*get_next_line(int fd);
size_t	ft_strlen(const char *str);
char	*gnl_strjoin(const char *s1, const char *s2);
int		istherenl(char *str);
char	*setup_stash(int fd, char *stash);
char	*free_wrapper(char *str);

#endif