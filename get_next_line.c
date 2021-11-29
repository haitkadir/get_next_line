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

static void iter_file_output(char **the_rest, char **temp, \
    char **buf, int *ret, int fd)
{
    while(!ft_strchr(*the_rest, '\n'))
    {
        *ret = read(fd, *buf, BUFFER_SIZE);
        if (*ret <= 0)
            break ;
        else
        {
            if(*the_rest)
            {
                *temp = ft_strjoin(*the_rest, *buf);
                if(!*temp)
                    return ;
                free(*the_rest);
                *the_rest = NULL;
            }
            else
                *temp = ft_strdup(*buf);
            *the_rest = *temp;
            *temp = NULL;
            ft_bzero(*buf, BUFFER_SIZE);
        }
    } 
}

static void the_recipe(char **the_rest, char **temp, char **line, int ret)
{
    if ((*the_rest) && (ft_strchr(*the_rest, '\n')))
    {
        *temp = *the_rest;
        *the_rest = NULL;
        *the_rest = ft_strdup((ft_strchr(*temp, '\n') + 1));
        if (!*the_rest)
            return ;
        ft_bzero((ft_strchr(*temp, '\n') + 1), ft_strlen((ft_strchr(*temp, '\n') + 1)));
        *line = ft_strdup(*temp);
        if (!*line)
            return ;
        free(*temp);
        *temp = NULL;
    }
    else if ((*the_rest && *the_rest[0]) && ret == 0)
    {
        *line = *the_rest;
        *the_rest = NULL;
    }
    else{
        // if(!*the_rest)
            free(*the_rest);
    }
}

char    *get_next_line(int fd)
{
    char        *buf;
    char        *line;
    char        *temp;
    static char *the_rest;
    int         ret;

    temp = NULL;
    line = NULL;
    if(!the_rest)
        the_rest = NULL;
    buf = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
    if (!buf)
        return (0);
    if (fd >= 0)
    {
        iter_file_output(&the_rest, &temp, &buf, &ret, fd);
        the_recipe(&the_rest, &temp, &line, ret);
    }
    if (buf)
        free (buf);
    return (line);
}
