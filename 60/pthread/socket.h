#ifndef SOCKET_H
#define SOCKET_H


#include <signal.h>
#include <syslog.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <pthread.h>
#include "become_daemon.h"
#include "inet_sockets.h"       /* Declarations of inet*() socket functions */
#include "tlpi_hdr.h"

unsigned short port = 8080;

#endif	/*SOCKET_H*/
