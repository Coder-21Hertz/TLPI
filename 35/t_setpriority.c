/*
 * 修改当前进程的nice值
 */
#include <sys/time.h>
#include <sys/resource.h>
#include "tlpi_hdr.h"

int main(int argc, char *argv[])
{
    if(argc !=3 || strchr("pgu", argv[1][0]) == NULL)
        usageErr("%s {p|g|u} who priority\n"
                "    set priority of: p=process; g=process group;"
                "u=processes for user\n", argv[0]);

    int which = (argv[1][0] == 'p') ? PRIO_PROCESS :
                    (argv[1][0] == 'g') ? PRIO_PGRP : PRIO_USER;
    id_t who = getpid();
    int prio = getInt(argv[2], 0, "prio");

    if(setpriority(which, who, prio) == -1)
        errExit("setpriority");
    errno = 0;
    prio = getpriority(which, who);
    if(prio == -1 && errno != 0)
        errExit("getpriority");

    printf("Nice value = %d\n", prio);

    exit(EXIT_SUCCESS);
}