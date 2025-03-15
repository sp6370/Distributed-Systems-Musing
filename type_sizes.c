
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("Size of off_t: %zu bytes\n", sizeof(off_t));
    printf("Size of off_t: %zu bytes\n", sizeof(int));
    printf("Size of off_t: %zu bytes\n", sizeof(size_t));
    printf("Size of off_t: %zu bytes\n", sizeof(ssize_t));
    return 0;
}
