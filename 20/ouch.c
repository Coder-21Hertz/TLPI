#include <signal.h>
#include "tlpi_hdr.h"

static void sigHandler(int sig)
{
    printf("Ouch!\n");
}

int main(int argc, char *argv[])
{
    if(signal(SIGINT, sigHandler) == SIG_ERR)
        errExit("signal");
    for(int j = 0; ;j++)
    {
        printf("%d\n", j);
        sleep(3);
    }
}
