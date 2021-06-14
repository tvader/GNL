/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvader <tvader@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 14:08:43 by tvader            #+#    #+#             */
/*   Updated: 2021/06/14 14:09:06 by tvader           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	linejoinrem(char **line, char **t_buf, char **s_buf)
{
	int	index;
	int	cnt;

	index = 0;
	cnt = 0;
	while ((*t_buf)[index] && (*t_buf)[index] != 10)
		index++;
	*line = (char *)ft_calloc(sizeof(char), index + 1);
	while (cnt < index)
	{
		(*line)[cnt] = (*t_buf)[cnt];
		cnt++;
	}
	if ((*t_buf)[cnt])
	{
		*s_buf = (char *)ft_calloc(sizeof(char), ft_strlen(*t_buf) - index + 1);
		cnt++;
	}
	index = 0;
	while ((*t_buf)[cnt])
	{
		(*s_buf)[index] = (*t_buf)[cnt];
		cnt++;
		index++;
	}
	free(*t_buf);
}

int 	isline(char *buf)
{
	int	i;

	i = 0;
	while (buf[i] && buf[i] != 10)
		i++;
	if (buf[i] == 10)
		return (1);
	return (0);
}

int	oldbuf(int	fd, short *s_fd, char **t_buf, char **s_buf)
{
	if (*s_fd == fd && s_buf && *s_buf)
	{
		ft_strlcat(*t_buf, *s_buf, ft_strlen(*s_buf) + 1);
		free(*s_buf);
		*s_buf = NULL;
	}
	else
	{
		*s_fd = fd;
		free(*s_buf);
		*s_buf = NULL;
	}
	return (0);
}

char	*expand(char **t_buf, size_t *tblen)
{
	char	*newbuf;

	if (tblen)
		*tblen *= 4;
	newbuf = (char *)ft_calloc(1, *tblen + 1);
	ft_strlcat(newbuf, *t_buf, *tblen + 1);
	free(*t_buf);
	return (newbuf);
}

int	get_next_line(int fd, char **line)
{
	char			*t_buf;
	int				cread;
	static char		*s_buf;
	static short	s_fd;
	size_t			tblen;

	if (BUFFER_SIZE == 0 || fd < 0)
		return (-1);
	tblen = ft_max(BUFFER_SIZE, TB_SIZE) + 1;
	t_buf = (char *)ft_calloc(sizeof(char), tblen);
	oldbuf(fd, &s_fd, &t_buf, &s_buf);
	while (!isline(t_buf))
	{
		if (tblen < ft_strlen(t_buf) + BUFFER_SIZE + 1)
			t_buf = expand(&t_buf, &tblen);
		cread = read(fd, t_buf + ft_strlen(t_buf), BUFFER_SIZE);
		if (!cread)
			break ;
	}
	if (isline(t_buf) || cread)
		linejoinrem(line, &t_buf, &s_buf);
	else
		return (freedom(&t_buf, line));
	return (1);
}
