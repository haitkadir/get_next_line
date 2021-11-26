#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"


int main(){
    int fd;
    char *str;
    // char *str1;

    fd = open("file.txt", O_RDONLY);
    int i = 7;
    while(i-- && str){
        str = get_next_line(fd);
        printf("%s", str);
    }
    // str1 = get_next_line(fd);
    // printf("%s", str1);
    return (0);
}