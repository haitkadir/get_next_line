#include "get_next_line.h"

char *get_next_line(int fd)
{
    char *buf;
    char *line;
    char *temp;
    static char *the_rest;
    int ret;

    temp = NULL;
    line = NULL;
    buf = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
    if (!buf)
        return (0);
    if (fd >= 0)
    {
        while(!ft_strchr(the_rest, '\n'))
        {
            ret = read(fd, buf, BUFFER_SIZE);
            if (ret <= 0)
                break ;
            if(ft_strlen(buf))
            {
                if(the_rest)
                {
                    temp = ft_strjoin(the_rest, buf);
                    if(!temp)
                        return (0);
                    free(the_rest);
                    the_rest = NULL;
                }
                else
                    temp = ft_strdup(buf);
                the_rest = ft_strdup(temp);
                if(!the_rest)
                    return (0);
                free(temp);
                temp = NULL;
                ft_bzero(buf, BUFFER_SIZE);
            }
        }

        if ((the_rest && the_rest[0] != '\0'))
        {
            if (ft_strchr(the_rest, '\n') && ft_strchr(the_rest, '\n') + 1)
            {
                temp = ft_strdup(the_rest);
                if(!temp)
                    return (0);
                free(the_rest);
                the_rest = NULL;
                the_rest = ft_strdup((ft_strchr(temp, '\n') + 1));
                if (!the_rest)
                    return (0);
                ft_bzero((ft_strchr(temp, '\n') + 1), ft_strlen((ft_strchr(temp, '\n') + 1)));
                line = ft_strdup(temp);
                if (!line)
                    return (0);
                free(temp);
                temp = NULL;
            }
            else if (ret == 0)
            {
                line = ft_strdup(the_rest);
                if (!line)
                    return (0);
                free(the_rest);
                the_rest = NULL;
            }
        }
    }

    free (buf);
    return (line);
}
