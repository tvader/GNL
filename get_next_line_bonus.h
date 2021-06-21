/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvader <tvader@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 11:06:01 by tvader            #+#    #+#             */
/*   Updated: 2021/06/21 23:20:54 by tvader           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# define TB_SIZE	1024
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif // !BUFFER_SIZE
typedef struct s_fds
{
	struct s_fds	*next;
	int				fd;
	int				is_eof;
	size_t			size;
	char			*buf;
}				t_fds;
int		get_next_line(int fd, char **line);
void	*ft_calloc(size_t count, size_t size);
size_t	ft_strlen(char *str);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_max(size_t s1, size_t s2);
int		isline(char *buf);
int		is_ended(t_fds *current_fd);
void	expand(t_fds	*cur);
void	freedom(t_fds **list, int fd);
#endif
