/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvader <tvader@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 14:08:43 by tvader            #+#    #+#             */
/*   Updated: 2021/06/21 23:13:06 by tvader           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	linejoinrem(char **line, char **t_buf, char **s_buf)
{
	int	index;
	int	cnt;

	index = 0;
	while ((*t_buf)[index] && (*t_buf)[index] != 10)
		index++;
	cnt = index;
	*line = (char *)ft_calloc(sizeof(char), index + 1);
	if (!(*line))
		return ;
	ft_strlcat(*line, *t_buf, index + 1);
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
	if (!(*t_buf))
	{
		if (*s_buf)
			free (*s_buf);
		return (-1);
	}
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
	if (!newbuf)
	{
		if (t_buf && *t_buf)
			free(*t_buf);
		return (NULL);
	}
	ft_strlcat(newbuf, *t_buf, *tblen + 1);
	if (t_buf && *t_buf)
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

	printf("BS = %d\n", BUFFER_SIZE);
	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, NULL, 0) < 0 || !line)
		return (-1);
	printf("1\n");
	tblen = ft_max(BUFFER_SIZE, TB_SIZE) + 1;
	t_buf = (char *)ft_calloc(sizeof(char), tblen);
	if (oldbuf(fd, &s_fd, &t_buf, &s_buf) < 0)
		return (-1);
	while (!isline(t_buf))
	{
		if (tblen < ft_strlen(t_buf) + BUFFER_SIZE + 1)
			t_buf = expand(&t_buf, &tblen);
		if (!t_buf)
			return (-1);
		cread = read(fd, t_buf + ft_strlen(t_buf), BUFFER_SIZE);
		if (cread <= 0)
			break ;
	}
	printf("4\n");
	return (endpart(&t_buf, &s_buf, line, cread));
}
