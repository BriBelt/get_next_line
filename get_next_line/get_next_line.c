/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 11:41:33 by bbeltran          #+#    #+#             */
/*   Updated: 2023/03/30 16:33:13 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
	{
		i++;
	}
	return (i);
}

char	*read_file(int fd, char *stored)
{
	char	*readline;
	char	*rawline;
	char	*previousread;
	int		rindex;

	rindex = 1;
	rawline = ft_substr(stored, 0, ft_strlen(stored));
	while (rindex != 0 && ft_strchr(rawline, '\n') == NULL)
	{
		readline = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (!readline)
			return (free(rawline), NULL);
		rindex = read(fd, readline, BUFFER_SIZE);
//		printf("rindex: %d", rindex);
//		printf("Buffer read: %s", readline);
		if (rindex < 0)
			return (free(readline), free(rawline), NULL);
		previousread = rawline;
		rawline = ft_strjoin(rawline, readline);
		free(previousread);
		free(readline);
	}
	return (free(stored), rawline);
}

char	*cut_and_paste(char *rawline)
{
	char	*newline;
	int		rawlen;
	int		foundchar;

	newline = 0;
	rawlen = ft_strlen(rawline);
	if (ft_strchr(rawline, '\n') == NULL && ft_strlen(rawline) > 0)
		newline = ft_substr(rawline, 0, ft_strlen(rawline));
	else if (ft_strlen(rawline) > 0)
	{
		foundchar = ft_strlen(ft_strchr(rawline, '\n'));
		newline = ft_substr(rawline, 0, rawlen - foundchar);
	}
	return (newline);
}

char	*cut_remainder(char *rawline)
{
	char	*remainder;
	char	*position_to_cut;

	remainder = 0;
	position_to_cut = ft_strchr(rawline, '\n');
	if (ft_strlen(position_to_cut) != 0)
		remainder = ft_substr(ft_strchr(rawline, '\n'), 0,
				ft_strlen(ft_strchr(rawline, '\n')));
	else if (ft_strlen(position_to_cut) == 0)
		remainder = 0;
	return (remainder);
}

char	*get_next_line(int fd)
{
	static char	*stored;
	char		*rawline;
	char		*newline;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	rawline = read_file(fd, stored);
	if (!rawline)
	{
		if (stored)
		{
			free(stored);
			stored = 0;
		}
		return (NULL);
	}
	newline = cut_and_paste(rawline);
	if (!newline && stored)
	{
		free(stored);
		return (NULL);
	}
	stored = cut_remainder(rawline);
	free(rawline);
	return (newline);
}
/*
int	main(void)
{
	int	fd;
	char	*newline;

	fd = open("only_three.txt", O_RDONLY);
	while ((newline = get_next_line(fd)))
	{
		printf("%s\n", newline);
		free(newline);
	}
	printf("%s\n", get_next_line(fd));
	printf("%s\n", get_next_line(fd));
	printf("%s\n", get_next_line(fd));
	
	fd = open("multiple_nl.txt", O_RDONLY);
	newline = get_next_line(fd);
	printf("\n1st --%s\n", newline);
	free(newline);
	newline = 0;
	newline = get_next_line(fd);
	printf("\n2nd --%s\n", newline);
	free(newline);
	newline = 0;
	newline = get_next_line(fd);
	printf("\n3rd --%s\n", newline);
	free(newline);
	newline = 0;
	newline = get_next_line(fd);
	printf("\n4th --%s\n", newline);
	free(newline);
	newline = 0;
	newline = get_next_line(fd);
	printf("\n5th --%s\n", newline);
	
	close(fd);
	return (0);
}*/
