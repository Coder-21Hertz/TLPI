#include "tlpi_hdr.h"

int main(int argc, char *argv[])
{
    printf("Hello world\n");
    fflush(stdout);
    write(STDOUT_FILENO, "Ciao\n", 5);

//    setbuf(stdout, NULL);

    switch(fork())
    {
        case -1:
            errExit("fork");
        case 0:
            _exit(EXIT_SUCCESS);
        default:
            exit(EXIT_SUCCESS);
    }
    exit(EXIT_SUCCESS);
}
