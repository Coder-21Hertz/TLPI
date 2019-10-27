#include <locale.h>
#include <time.h>
#include <sys/time.h>
#include "tlpi_hdr.h"
#define SECONDS_IN_TROPICAL_YEAR (365.24219*24*60*60)

int main(int argc, char *argv[])
{
    time_t t;
    struct tm *gmp, *locp;
    struct tm gm, loc;
    struct timeval tv;

    t = time(NULL);
    printf("Seconds since the Epoch (1 Jan 1970): %ld\n",(long)t);
    printf("about %6.3f years\n", t/SECONDS_IN_TROPICAL_YEAR);

    if(gettimeofday(&tv, NULL) == -1)
        errExit("gettimeofday");
    printf("gettimeofday() returned %ld secs,%ld microsecs\n",
            (long)tv.tv_sec, (long)tv.tv_usec);

    gmp = gmtime(&t);
    if(gmp == NULL)
        errExit("gmtime");
    gm = *gmp;
    printf("Broken down by gmmtime():\n");
    //年：和1900年之差；月：从0开始到11
    printf(" year=%d mon=%d mday=%d hour=%d min=%d sec=%d ",gm.tm_year,
            gm.tm_mon, gm.tm_mday, gm.tm_hour, gm.tm_min, gm.tm_sec);
    //wday：星期几，Sunday=0； yady：一年中的第几天，1月1=0；isdst：夏令时标志
    printf("wday=%d yday=%d isdst=%d\n", gm.tm_wday, gm.tm_yday, gm.tm_isdst);
    //标准输出
    printf("%d-%d-%d\n", gm.tm_year+1900, gm.tm_mon+1, gm.tm_mday);

    locp = localtime(&t);
    if(locp == NULL)
        errExit("localtime");
    loc = *locp;

    printf("Broken down by localtime():\n");
    printf(" year=%d mon=%d mday=%d hour=%d min=%d sec=%d ",
            loc.tm_year, loc.tm_mon, loc.tm_mday,
            loc.tm_hour, loc.tm_min, loc.tm_sec);
    printf("wday=%d yday=%d isdst=%d\n\n",
            loc.tm_wday, loc.tm_yday, loc.tm_isdst);

    printf("asctime() formats the gmtime() value as: %s\n", asctime(&gm));
    printf("ctime() formats the time() valus as:     %s\n", ctime(&t));

    printf("mktime() of gmtime() value:    %ld secs\n", (long) mktime(&gm));
    printf("mktime() of localtime() value: %ld secs\n", (long) mktime(&loc));

    exit(EXIT_SUCCESS);
}
