#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*stored;
	char	*newline;
	char	*aux;

}

char	*ft_readline(int fd, char *stored)
{
	char	*readline;
	int	rindex;
	char	*aux;

	rindex = 1;
	readline = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!readline)
		return (NULL);
	ft_bzero(readline, BUFFER_SIZE + 1);
	while (rindex >= 0)
	{
		rindex = read(fd, readline, BUFFER_SIZE);
		if (rindex < 0)
		{
			free(readline);
			free(stored);
			readline = 0;
			stored = 0;
			return (NULL);
		}
		if (rindex == 0 && readline)
		{
			stored = ft_strjoin(stored, readline);
			free(readline);
			readline = 0;
			return(stored);
		}
		if (ft_strchr(stored, '\n') == NULL)
			stored = ft_strjoin(stored, readline);
	}
			free(readline);
	return (stored);		
}
