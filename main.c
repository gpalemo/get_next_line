/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmauley <cmauley@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 17:21:28 by cmauley           #+#    #+#             */
/*   Updated: 2025/11/15 16:10:42 by cmauley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h> // open
#include <stdio.h> // printf
#include <unistd.h> // close

int	main()
{
	int	fd;
	int	i;
	char	*line;
	
	fd = open ("test.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("error\n");
		return (-1);
	}
	i = 1;
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("CALL %d : [%s]\n", i, line);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	close(fd);
	return (0);
}