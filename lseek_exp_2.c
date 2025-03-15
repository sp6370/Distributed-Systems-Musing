#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

/*
Intent: Investigate the behaviour of lseek with SEEK_END when offset value used is negative

Expectation: lseek positions the cursor at the "offset" bytes before the EOF

Result: Matches the expectation
*/

int main()
{
    char *file_path = "xkcd_10k.txt";
    int fd = open(file_path, O_RDONLY);
    if (fd == -1)
    {
        perror("ERROR: opening the file");
        return 1;
    }

    int op_result = lseek(fd, -100, SEEK_END);
    if (op_result == -1)
    {
        perror("ERROR: on performing lseek");
        close(fd);
        return 1;
    }

    char buf[100];
    int read_op_result = read(fd, buf, 100);
    if (read_op_result == -1)
    {
        perror("ERROR: on reading from the file");
        close(fd);
        return 1;
    }

    printf("INFO: Result of read_op %d \n", read_op_result);

    // print the data read => should be last 100 characters from the file
    for (int i = 0; i < read_op_result; i++)
    {
        printf("%c", buf[i]);
    }

    close(fd);
    return 0;
}