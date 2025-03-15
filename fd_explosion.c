#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

/*
Intent: Investigate the behaviour of program when too many fd's are requested from the kernel

Expectation: program crashes

Result: Meets the expectation, open starts returning errors after 60K fd allocations
*/

int main()
{
    char *file_path = "xkcd_10k.txt";

    for (int i = 0; i < 10000000; i++)
    {
        int fd = open(file_path, O_RDONLY);
        if (fd == -1)
        {
            perror("ERROR: opening the file");
            return 1;
        }

        printf("INFO: fd allocated %d \n", fd);
    }

    // bad practice the fd's are not closed
    return 0;
}