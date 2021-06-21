/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvader <tvader@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 11:04:57 by tvader            #+#    #+#             */
/*   Updated: 2021/06/21 23:13:05 by tvader           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	while (*str++)
		len++;
	return (len);
}

size_t	ft_max(size_t s1, size_t s2)
{
	if (s1 >= s2)
		return (s1);
	return (s2);
}

void	*ft_calloc(size_t count, size_t size)
{
	void			*res;
	unsigned int	cnt;

	cnt = 0;
	res = (void *)malloc(count * size);
	if (res)
	{
		while (cnt < count * size)
		{
			*(char *)(res + cnt) = 0;
			cnt++;
		}
		return (res);
	}
	else
		return (NULL);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	cnt;
	size_t	dlen;
	size_t	slen;

	cnt = 0;
	dlen = ft_strlen((char *)dst);
	slen = ft_strlen((char *)src);
	if (dlen > dstsize)
		return (dstsize + slen);
	while (src[cnt])
	{
		if (cnt + dlen + 1 >= dstsize)
			break ;
		dst[cnt + dlen] = src[cnt];
		cnt++;
	}
	dst[cnt + dlen] = 0;
	while (cnt + dlen < dstsize && cnt + 1 == slen)
	{
		dst[cnt + dlen] = 0;
		cnt++;
	}
	if (dstsize > dlen + slen)
		return (slen + dlen);
	return (dlen + slen + (cnt + slen < dstsize) * (cnt));
}

int	endpart(char **t_buf, char **s_buf, char **line, int cread)
{
	if (cread < 0)
	{
		free(*t_buf);
		return (-1);
	}
	linejoinrem(line, t_buf, s_buf);
	if (!(*line))
	{
		free(*t_buf);
		return (-1);
	}
	if (!cread && !((*s_buf)))
		return (0);
	return (1);
}
