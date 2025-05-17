#include "get_next_line.h"

char *ft_strdup(char *src)
{
    int i = 0;
    char *dest;
    while (src[i])
        i++;
    dest = malloc(sizeof(char) * (i + 1));
    i = 0;
    while (src[i])
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return (dest);
}

char    *get_next_line(int fd)
{
    static char buffer[BUFFER_SIZE];
    static int buffer_pos = 0;
    static int pos = 0;
    char line[70000];
    int i = 0;
    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    while (1)
    {
        if (buffer_pos <= pos)
        {
            buffer_pos = read(fd, buffer, BUFFER_SIZE);
            pos = 0;
            if (buffer_pos <= 0)
                break;
        }
        line[i] = buffer[pos++];
        if (line[i++] == '\n')
            break;
    }
    if (i == 0)
        return (NULL);
    line[i] = '\0';
    return (ft_strdup(line));
}

#include <stdio.h>

int main(void)
{
	int fd = open("test.txt", O_RDONLY);
	char *line;

	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}