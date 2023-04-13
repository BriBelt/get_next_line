/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbeltran <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:53:06 by bbeltran          #+#    #+#             */
/*   Updated: 2023/03/22 16:11:57 by bbeltran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*newstr;
	char	*ptr;
	size_t	newssize;
	size_t	lens1;
	size_t	lens2;

	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	newssize = lens1 + lens2;
	newstr = ft_calloc(newssize + 1, sizeof(char));
	ptr = newstr;
	if (!newstr || !ptr)
		return (0);
	while (s1 && *s1)
		*newstr++ = *s1++;
	while (s2 && *s2)
		*newstr++ = *s2++;
	return (ptr);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	slen;

	slen = ft_strlen(src);
	i = 0;
	if (!src && !dst)
		return (slen);
	if (!dstsize)
		return (slen);
	while (src[i] != '\0' && i < (dstsize - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (slen);
}

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (NULL);
	while (str && str[i])
	{
		if (str[i] == c)
			return ((char *)&str[i + 1]);
		else
			i++;
	}
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sbstr;
	size_t	slen;

	slen = ft_strlen(s);
	if (start >= slen)
		start = slen;
	if (len > slen)
		len = slen - start;
	if (!s)
		return (0);
	if (s && s[start] == 0)
		len = 0;
	if (start + len > slen)
		len = ft_strlen(s + start);
	sbstr = malloc((len + 1) * sizeof(char));
	if (!sbstr)
		return (0);
	ft_strlcpy(sbstr, s + start, len + 1);
	return (sbstr);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;
	size_t	i;
	size_t	n;

	p = malloc(count * size);
	if (!p)
		return (NULL);
	i = 0;
	n = count * size;
	while (i < n)
	{
		((char *)p)[i] = '\0';
		i++;
	}
	return (p);
}
