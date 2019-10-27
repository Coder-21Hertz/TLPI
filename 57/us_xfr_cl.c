#include "us_xfr.h"

int main(int argc, char *argv[])
{
    struct sockaddr_un addr;
    ssize_t numRead;
    char buf[BUF_SIZE];

    int sfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if(sfd == -1)
        errExit("socket");

    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SV_SOCK_PATH, sizeof(addr.sun_path)-1);

    if(connect(sfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_un)) == -1)
        errExit("connect");

    while((numRead = read(STDIN_FILENO, buf, BUF_SIZE)) > 0)
        if(write(sfd, buf, numRead) != numRead)
            fatal("partial/failed write");

    if(numRead == -1)
        errExit("read");

    exit(EXIT_SUCCESS);
}
