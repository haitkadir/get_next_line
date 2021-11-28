#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"


int main(){
    int fd;
    char *str;
    // char *str1;

    fd = open("file.txt", O_RDONLY);
    // int i = 10000000;
    // str = get_next_line(fd);
    while(1)
    {
        str = get_next_line(fd);
        if (!str)
            break;
        else
            printf("%s", str);
        free(str);
    }
    return (0);
}