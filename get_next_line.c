#include "get_next_line.h"

static int if_contean(char *str, char c)
{
    int i;

    if(!str)
        return (0);
    i = 0;
    while(str[i])
        if(str[i++] == c)
            return (1);
    
    return (0);
}

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
    if (fd >= 0)
    {
        while(!if_contean(the_rest, '\n'))
        {
            ret = read(fd, buf, BUFFER_SIZE);
            if (ret <= 0){
                break ;
            }

            if(ft_strlen(buf))
            {
                if(the_rest)
                {
                    temp = ft_strjoin(the_rest, buf);
                    free(the_rest);
                    the_rest = NULL;
                }
                else{
                    temp = ft_strdup(buf);
                }
                the_rest = ft_strdup(temp);
                free(temp);
                temp = NULL;
                ft_bzero(buf, BUFFER_SIZE);
            }
        }

        if ((the_rest && the_rest[0] != '\0'))
        {
            if (if_contean(the_rest, '\n') && ft_strchr(the_rest, '\n') + 1)
            {
                temp = ft_strdup(the_rest);
                free(the_rest);
                the_rest = NULL;
                the_rest = ft_strdup((ft_strchr(temp, '\n') + 1));
                ft_bzero((ft_strchr(temp, '\n') + 1), \
                    ft_strlen((ft_strchr(temp, '\n') + 1)));
                line = ft_strdup(temp);
                free(temp);
                temp = NULL;
            }
            else if (ret == 0)
            {
                line = ft_strdup(the_rest);
                free(the_rest);
                the_rest = NULL;
            }
        }
    }

    free (buf);
    return (line);
}
