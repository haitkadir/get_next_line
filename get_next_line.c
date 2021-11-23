#include "get_next_line.h"


char *get_next_line(int fd)
{
    static char buf[BUFFER_SIZE];
    char *substring;
    char *temp;
    char *line;
    char *test;
    size_t read_return;
    int i;
    int j;

    i = 0;
    read_return = 10;
    test = ft_strdup(buf);
    temp = ft_calloc(1, sizeof(char));
    if(ft_strlen(buf) > 0)
    {
        temp = ft_strdup(ft_strchr(buf, '\n'));
    }
    //buf = (char *)ft_calloc(BUFFER_SIZE + 1,   sizeof(char));
    if(fd >= 0)
    {
        while(read_return > 0){
            read_return = read(fd, buf, 10);
            j = 0;
            while(buf[j])
                if(buf[j++] == '\n')
                {
                    read_return = 0;
                    break ;
                }
            if(buf[j] == '\0' || buf[j - 1] == '\n')
            {
                substring = ft_substr(buf, 0, j);
                line = ft_strjoin(temp, substring);
                temp = ft_strdup(line);
            }
            i++;
        }
    }
    return (line);
}
