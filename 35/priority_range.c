#include <sched.h>
#include "tlpi_hdr.h"

int main(int argc, char *argv[])
{
    int min_1 = sched_get_priority_min(SCHED_RR);
    int max_1 = sched_get_priority_max(SCHED_RR);
    int min_2 = sched_get_priority_min(SCHED_FIFO);
    int max_2 = sched_get_priority_max(SCHED_FIFO);

    printf("SCHED_RR_min = %d\n", min_1);
    printf("SCHED_RR_max = %d\n", max_1);
    printf("SCHED_FIFO_min = %d\n", min_2);
    printf("SCHED_FIFO_max = %d\n", max_2);

    exit(EXIT_SUCCESS);
}
