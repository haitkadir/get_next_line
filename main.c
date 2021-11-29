#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"


int main(){
    int fd;
    char *str;
    // char *str1;

    fd = open("file.txt", O_RDONLY);
    int i = 5;
    // str = get_next_line(fd);
    while(i--)
    {
        str = get_next_line(fd);
            printf("%s", str);
        free(str);
    }
    return (0);
}