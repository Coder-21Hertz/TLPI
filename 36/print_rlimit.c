#include "print_rlimit.h"

int printRlimit(const char *msg, int resource)
{
    struct rlimit rlim;

    if(getrlimit(resource, &rlim) == -1)
        errExit("getrlimit");

    printf("%s: soft=", msg);
    if(rlim.rlim_cur == RLIM_INFINITY)
        printf("infinite");
#ifdef RLIM_SAVED_CUR
    else if(rlim.rlim_cur == RLIM_SAVED_CUR)
        printf("unrepresentable");
#endif
    else
        printf("%lld", (long long) rlim.rlim_cur);

    printf("; hard=");
    if(rlim.rlim_max == RLIM_INFINITY)
        printf("infinite");
#ifdef RLIM_SAVED_MAX
    else if(rlim.rlim_max == RLIM_SAVED_MAX)
        printf("unrepresentable");
#endif
    else
        printf("%lld\n", (long long) rlim.rlim_max);

    return 0;
}
