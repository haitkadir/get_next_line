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

static void cndtion1(char *line, char *after_n_line)
{
    if(after_n_line){
        line = ft_strjoin(line, after_n_line);
        free(after_n_line);
        after_n_line = NULL;
    }
}

static int cndtion2(char *buf, char *after_n_line, int read_return)
{
    if(if_contean(buf, '\n'))
    {
        after_n_line = ft_strdup(ft_strchr(buf, '\n') + 1);
        read_return = 0;
    }
    return (read_return);
}


char *get_next_line(int fd)
{
    char *buf;
    char *line;
    char *temp;
    static char *statiq;
    int ret;

    statiq = (char *)ft_calloc(1, sizeof(char));
    if (fd >= 0)
    {
        buf = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
        temp = line = NULL;
        ret = 1;
        while(ret)
        {
            if (statiq && statiq[0] != '\0' && (if_contean(statiq, '\n') || ret == 0))
            {
                if (if_contean(statiq, '\n'))
                {
                    temp = ft_strdup(statiq);
                    ft_bzero((ft_strchr(temp, '\n') + 1), ft_strlen((ft_strchr(temp, '\n') + 1)));
                    line = ft_strdup(temp);
                    free(temp);
                    statiq = ft_strdup((ft_strchr(statiq, '\n') + 1));
                    break ;
                }
                else
                {
                    line = ft_strdup(statiq);
                    if(statiq)
                        ft_bzero(statiq, ft_strlen(statiq));
                    break ;
                }
            }
            else
            {
                ret = read(fd, buf, BUFFER_SIZE);
                buf[BUFFER_SIZE] = '\0';
                if(ft_strlen(buf))
                {
                    temp = ft_strjoin(statiq, buf);
                    free(statiq);
                    statiq = ft_strdup(temp);
                    free(temp);
                    temp = NULL; 
                    ft_bzero(buf, BUFFER_SIZE);
                }
            }
        }
    }
    free (buf);
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
