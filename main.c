#include <fcntl.h>
#include <stdio.h>
#include "get_next_line_bonus.h"


int main(){
    int fd1;

    char *str;
    // char *str1;

    fd1 = open("main.c", O_RDONLY);

    // int i = 2;

    while(1)
    {
        str = get_next_line(fd1);
        if(!str)
            break;
        else
            printf("%s", str);
        free(str);
    }
    //printf("%s", get_next_line(fd1));


    return (0);
}