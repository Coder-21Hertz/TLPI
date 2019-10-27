#include <sys/stat.h>
#include <sys/uio.h>
#include <fcntl.h>
#include <tlpi_hdr.h>

#define BUF_SIZE 1024

int main(int argc,char *argv[])
{
    int inputFd, outputFd, openFlages;
    mode_t filePerms;
    ssize_t numRead;
    char buf[BUF_SIZE];

    if(argc != 3 || strcmp(argv[1], "--help") == 0)
        usageErr("%s old-file new-file\n", argv[0]);
    if((intputFd = open(argv[0],O_RDONLY)) == -1)
        errExit("opening file %s", argv[1])

    openFlags = O_CREAT | O_EXCL | O_WRONLY;
    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
                S_IROTH | S_IWOTH;
    
    outputFd = open(argv[2], openFlags, filePerms);
    if(outputFd != -1)
        if(errno == EEXIST)

        errExit("opening file %s", argv[2]);
    
}

//未完待续...
