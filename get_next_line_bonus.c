/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvader <tvader@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 11:05:24 by tvader            #+#    #+#             */
/*   Updated: 2021/06/22 04:46:11 by tvader           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_fds	*fd_in_list(t_fds **list, int fd)
{
	t_fds	*new;

	new = NULL;
	if (list && *list)
	{
		new = *list;
		while (new->fd != fd && new->next)
			new = new->next;
	}
	if (!new || new->fd != fd)
	{
		new = malloc(sizeof(t_fds));
		if (!new)
			return (NULL);
		new->size = BUFFER_SIZE;
		new->buf = (char *)ft_calloc(new->size + 1, sizeof(char));
		if (!(new->buf))
			return (NULL);
		new->fd = fd;
		new->is_eof = 0;
		new->next = *list;
		*list = new;
	}
	return (new);
}

int	readline(t_fds *cur)
{
	int		cread;

	cread = 1;
	if (!cur)
		return (-1);
	while (!isline(cur->buf) && cread)
	{
		while (ft_strlen(cur->buf) + BUFFER_SIZE + 1 > cur->size)
			expand(cur);
		if (!cur)
			return (-1);
		cread = read(cur->fd, cur->buf + ft_strlen(cur->buf), BUFFER_SIZE);
	}
	if (!cread && !isline(cur->buf))
		cur->is_eof = 1;
	return (0);
}

int	createline(t_fds *current_fd, char **line)
{
	int		linelen;
	int		cnt;
	size_t	blen;

	if (!current_fd)
		return (-1);
	blen = ft_strlen(current_fd->buf);
	linelen = 0;
	while ((current_fd->buf)[linelen] && (current_fd->buf)[linelen] != 10)
		linelen++;
	*line = (char *)ft_calloc(linelen + 1, sizeof(char));
	if (!(*line))
		return (-1);
	cnt = 0;
	ft_strlcat(*line, current_fd->buf, linelen + 1);
	while ((size_t)cnt < blen)
	{
		if (cnt < (int) blen - linelen)
			(current_fd->buf)[cnt] = (current_fd->buf)[cnt + linelen + 1];
		else
			(current_fd->buf)[cnt] = 0;
		cnt++;
	}
	return (0);
}

void	freedom(t_fds ***list, int fd)
{
	t_fds	*victim;
	t_fds	*prev;

	if (!(*list))
		return ;
	victim = **list;
	prev = NULL;
	while (victim->fd != fd)
	{
		prev = victim;
		victim = victim->next;
	}
	if (prev)
		prev->next = victim->next;
	else if (!prev && victim->next)
		**list = victim->next;
	else
		**list = NULL;
	free(victim->buf);
	free(victim);
	if (!(**list))
	{
		free(*list);
		*list = NULL;
	}
}

int	get_next_line(int fd, char **line)
{
	static t_fds	**s_beg_list;
	t_fds			*current_fd;

	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, NULL, 0) < 0 || !line)
		return (-1);
	if (!s_beg_list)
		s_beg_list = ft_calloc(1, sizeof(t_fds **));
	if (!s_beg_list)
		return (-1);
	current_fd = fd_in_list(s_beg_list, fd);
	if (readline(current_fd) || createline(current_fd, line))
	{
		freedom(&s_beg_list, fd);
		return (-1);
	}
	if (!(current_fd->is_eof))
		return (1);
	else if (s_beg_list)
		freedom(&s_beg_list, fd);
	return (0);
}
