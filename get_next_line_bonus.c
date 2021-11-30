/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haitkadi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 21:37:16 by haitkadi          #+#    #+#             */
/*   Updated: 2021/11/28 21:37:21 by haitkadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

void	ft_bzero(void *s, size_t n)
{
	char	*str;

	str = (char *)s;
	while (n > 0)
	{
		*str++ = '\0';
		n--;
	}
}

static	void	iter_file_output(char **line, \
	char **buf, int *ret, int fd)
{
	char	*temp;

	while (!ft_strchr(*line, '\n'))
	{
		*ret = read(fd, *buf, BUFFER_SIZE);
		if (*ret <= 0)
			break ;
		else
		{
			if (*line)
			{
				temp = *line;
				*line = ft_strjoin(*line, *buf);
				free(temp);
				if (!*line)
					return ;
			}
			else
				*line = ft_strdup(*buf);
			ft_bzero(*buf, BUFFER_SIZE);
		}
	}
}

static	void	the_recipe(char **the_rest, char **line, int fd)
{
	char	*temp;
	char	*ptr_to_nl;

	ptr_to_nl = NULL;
	if (ft_strchr(*line, '\n'))
		ptr_to_nl = ft_strchr(*line, '\n');
	temp = 0;
	if (ptr_to_nl && *(ptr_to_nl + 1))
	{
		temp = *line;
		*line = 0;
		the_rest[fd] = ft_strdup(ft_strchr(temp, '\n') + 1);
		if (!the_rest[fd])
			return ;
		ft_bzero(ft_strchr(temp, '\n') + 1, \
			ft_strlen((ft_strchr(temp, '\n') + 1)));
		*line = ft_strdup(temp);
		free(temp);
		if (!line)
			return ;
	}
}

char	*get_next_line(int fd)
{
	char		*buf;
	char		*line;
	static char	*the_rest[1024];
	int			ret;

	line = NULL;
	buf = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buf)
		return (0);
	if (fd >= 0)
	{
		if (the_rest[fd])
		{
			line = ft_strdup(the_rest[fd]);
			if (!line)
				return (0);
			free(the_rest[fd]);
			the_rest[fd] = 0;
		}
		iter_file_output(&line, &buf, &ret, fd);
		the_recipe(the_rest, &line, fd);
	}
	free(buf);
	return (line);
}
