#include "get_next_line.h"

static int if_contean(char *str, char c)
{
    int i;

    i = 0;
    while(str[i])
        if(str[i++] == c)
            return (1);
    
    return (0);
}

char *get_next_line(int fd)
{
    char buf[BUFFER_SIZE + 1];
    char *temp;
    char *line;
    static char *after_n_line;
    int read_return;
    int i;

    read_return = 1;
    i = 0;
    while(read_return)
    {
        read_return = read(fd, buf, BUFFER_SIZE);
        buf[BUFFER_SIZE] = '\0';
        while(buf[i] && buf[i] != '\n')
            i++;
        temp = ft_substr(buf, 0, i);
        if(if_contean(buf, '\n'))
        {
            after_n_line = ft_strdup(ft_strchr(buf, '\n'));
            read_return = 0;
        }
        else
        {
            line = ft_strjoin(temp, after_n_line);
            free(temp);
            free(after_n_line);
        }
        temp = line;
    }
    if(!line)
        return (0);
    return (line);
}





















































// char *get_next_line(int fd)
// {
//     static char buf[BUFFER_SIZE + 1];
//     char *substring;
//     char *temp;
//     char *line;
//     int read_return;
//     int i;
//     int j;

//     i = 0;
//     read_return = 1;
//     temp = ft_calloc(1, sizeof(char));
//     if(fd >= 0)
//     {
//         while(read_return > 0){
//             j = 0;
//             while(buf[j])
//             {
//                 if(buf[j] == '\n' && buf[j + 1] != 0)
//                 {
//                     temp = ft_substr(buf, j + 1, ft_strlen(buf) - j);
//                 }
//                 j++;
//             }
//             read_return = read(fd, buf, BUFFER_SIZE);
//             //printf("\n\nbuf: %s \n\n", buf);
//             buf[BUFFER_SIZE] = '\0';
//             j = 0;
//             while(buf[j])
//                 if(buf[j++] == '\n')
//                 {
//                     read_return = 0;
//                     break ;
//                 }
//             if(buf[j] == '\0' || buf[j - 1] == '\n' || read_return < j)
//             {
//                 if(read_return != 0)
//                     j = read_return;
//                 substring = ft_substr(buf, 0, j);
//                 line = ft_strjoin(temp, substring);
//                 temp = ft_strdup(line);
//             }
//             if(read_return == 0)
//                 break;
//             i++;
//         }
//     }
//     if(!line)
//         return (0);
//     return (line);
// }
