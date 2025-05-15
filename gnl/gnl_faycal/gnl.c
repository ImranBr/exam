#include "gnl.h"

char	*ft_strdup(const char *src)
{	
	int		i;
	char	*dest;

	i = 0;
	while (src[i])
		i++;
	dest = malloc(sizeof(char) * (i + 1));
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*get_next_line(int fd)
{
	static char buffer[BUFFER_SIZE];
	static int bytes_read = 0;
	static int buffer_index = 0;
	char line[70000];
	int i = 0;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		if (buffer_index >= bytes_read)
		{
			bytes_read = read(fd, buffer, BUFFER_SIZE);
			buffer_index = 0;
			if (bytes_read <= 0)
				break ;
		}
		line[i] = buffer[buffer_index++];
		if (line[i++] == '\n')
			break ;
	}
	if (i == 0)
		return (NULL);
	line[i] = '\0';
	return (ft_strdup(line));
}