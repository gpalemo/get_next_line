#include <fcntl.h>
#include <stdio.h>
#include "get_next_line_bonus.h"

int main(void)
{
	int fd1 = open("file1.txt", O_RDONLY);
	int fd2 = open("file2.txt", O_RDONLY);

	if (fd1 < 0 || fd2 < 0)
	{
		printf("Error\n");
		return (1);
	}

	char *line1;
	char *line2;

	while (1)
	{
		line1 = get_next_line(fd1);
		line2 = get_next_line(fd2);

		if (!line1 && !line2)
			break;

		if (line1)
		{
			printf("fd1: %s", line1);
			free(line1);
		}
		if (line2)
		{
			printf("fd2: %s", line2);
			free(line2);
		}
	}

	close(fd1);
	close(fd2);
	return (0);
}
