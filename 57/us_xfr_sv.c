#include "us_xfr.h"

#define BACKLOG 5

int main(int argc, char *argv[])
{
    struct sockaddr_un addr;
    ssize_t numRead;
    char buf[BUF_SIZE];

    int sfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if(sfd == -1)
        errExit("socket");
    
    if(remove(SV_SOCK_PATH) == -1 && errno != ENOENT)
        errExit("remove-%s", SV_SOCK_PATH);

    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SV_SOCK_PATH, sizeof(addr.sun_path)-1);

    if(bind(sfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_un)) == -1)
        errExit("bind");

    if(listen(sfd, BACKLOG) == -1)
        errExit("listen");

    for(;;){
        int cfd = accept(sfd, NULL, NULL);
        if(cfd == -1)
            errExit("accept");

        while((numRead = read(cfd, buf, BUF_SIZE)) > 0)
            if(write(STDOUT_FILENO, buf, numRead) != numRead)
                fatal("partial/failed write");

        if(numRead == -1)
            errExit("read");
        if(close(cfd) == -1)
            errMsg("close");
    }
}
