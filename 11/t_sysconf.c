#include <stdio.h>
#include <tlpi_hdr.h>

static void sysconfPrint(const char *msg, int name)
{
    long lim;

    errno = 0;
    lim = sysconf(name);
    if(lim != -1){
        printf("%s\t%ld\n", msg, lim);
    }else{
        if(errno == 0)
            printf("%s (indeterminate)\n", msg);
        else
            errExit("sysconf %s", msg);
    }
}

int main(int argc, char *argv[])
{
    sysconfPrint("_SC_ARG_MAX:", _SC_ARG_MAX);
    sysconfPrint("_SC_LOGIN_NAME_MAX:", _SC_LOGIN_NAME_MAX);

    exit(EXIT_SUCCESS);
}
