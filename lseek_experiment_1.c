#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

/*
Intent: Investigate the behaviour of lseek with SEEK_END,
        but the user wants to go beyond the file end.

Expectation: lseek returns error i.e -1

Result: It doesn't return an error, but rather you are allowed to go beyond the end of file.
        If  data  is  later  written at this point, subsequent reads of the data
        in the gap (a "hole") return null bytes ('\0') until data is actually written into the gap.

        Reading after going beyond the end of the file. => read says end of file reached
*/

int main() {
    char *file_path = "xkcd_10k.txt";
    
    int fd = open(file_path, O_RDONLY);
    if (fd == -1){
        perror("ERROR: opening the file");
        return 1;
    }

    int op_result = lseek(fd, 100, SEEK_END); // from the file end move 100 postion to the right
    if (op_result == -1){
        perror("ERROR: on performing lseek");
        return 1;
    }
    
    printf("INFO: Result of lseek %d \n", op_result); // It doesn't return an error. Refer to man page.

    char read_buffer[100];
    
    int read_op_result = read(fd, read_buffer, 100);
    if (read_op_result == -1){
        perror("ERROR: can't read after lseek beyond end in file");
    }

    if (read_op_result == 0){
        printf("WARN: read says end of file reached\n");
        return 0;
    }

    printf("INFO: printing the read buffer\n");

    for (int i = 0; i < read_op_result; i++) {
        printf("%c", read_buffer[i]);
    }
    
    return 0;
}