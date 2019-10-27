#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "tlpi_hdr.h"

int main(int argc, char *argv[])
{
    char template[] = "/tmpitestXXXXXX";

    setbuf(stdout, NULL);

    int fd = mkstemp(template);
    if(fd == -1)
        errExit("mkstemp");

    printf("File offset before fork(): %lld\n",
            (long long)lseek(fd, 0, SEEK_CUR));

    int flags = fcntl(fd, F_GETFL);
    if(flags == -1)
        errExit("fcntl - F_GETFL");
    printf("O_APPEND falg before fork() is: %s\n",
            (flags & O_APPEND) ? "on" : "off");

    switch(fork())
    {
        case -1:
            errExit("fork");
        case 0:
            if(lseek(fd, 1000, SEEK_SET) == -1)
                errExit("lseek");
            flags = fcntl(fd, F_GETFL);
            if(flags == -1)
                errExit("fcntl - F_GETFL");
            flags |= O_APPEND;
            if(fcntl(fd, F_SETFL, flags) == -1)
                errExit("fcntl - F_SETFL");
        _exit(EXIT_SUCCESS);
        
        default:
            if(wait(NULL) == -1)
                errExit("wait");
            printf("Child has exited\n");

            printf("File offset in parent: %lld\n", 
                    (long long)lseek(fd, 0, SEEK_CUR));

            flags = fcntl(fd, F_GETFL);
            if(flags == -1)
                errExit("fcntl - F_GETFL");
            printf("O_APPEND flag in parent is: %s\n",
                    (flags & O_APPEND) ? "on" : "off");
            exit(EXIT_SUCCESS);
    }
}
