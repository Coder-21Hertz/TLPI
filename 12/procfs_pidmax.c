#include <fcntl.h>
#include "tlpi_hdr.h"

#define MAX_LINE 100

int main(int argc, char *argv[])
{
    int fd;
    char line[MAX_LINE];

    fd = open("/proc/sys/kernel/pid_max", (argc > 1) ? O_RDWR : O_RDONLY);
    if(fd == -1)
        errExit("open");
    ssize_t n = read(fd, line, MAX_LINE);
    if(n == -1)
        errExit("read");

    if(argc > 1)
        printf("Old value: ");
    printf("%.*s", (int)n, line);
//    system("cat /proc/sys/kernel/pid_max");

    if(argc > 1){
        printf("%s\n", argv[1]);
        if(write(fd, argv[1], strlen(argv[1])) != strlen(argv[1]))
            fatal("write() failed");
        
        printf("%s\n", argv[1]);
        system("echo /proc/sys/kernel/pid_max now contains "
                "`cat /proc/sys/kernel/pid_max`");
    }

    exit(EXIT_SUCCESS);
}
