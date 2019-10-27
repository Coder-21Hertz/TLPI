#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include "tlpi_hdr.h"

int main(int argc, char *argv[])
{
    printf("uid = %d, gid = %d, euid = %d, egid = %d\n",
            getuid(), getgid(), geteuid(), getegid());

    exit(EXIT_SUCCESS);
}
