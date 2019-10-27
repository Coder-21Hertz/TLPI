#include <dlfcn.h>
#include "tlpi_hdr.h"

int main(int argc, char *argv[])
{
    if(argc != 3 || strcmp(argv[1], "--help") == 0)
        usageErr("%s lib-path func-name\n", argv[0]);

    void *libHandle = dlopen(argv[1], RTLD_LAZY);
    if(libHandle == NULL)
        fatal("dlopen: %s", dlerror());

    (void) dlerror();
    void (*funcp)(void);
    *(void **)(&funcp) = dlsym(libHandle, argv[2]);
    const char *err = dlerror();
    if(err != NULL)
        fatal("dlsym: %s", err);

    if(funcp == NULL)
        printf("%s is NULL\n", argv[2]);
    else
        (*funcp)();

    dlclose(libHandle);

    exit(EXIT_SUCCESS);
}
