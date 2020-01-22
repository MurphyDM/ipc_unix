//
//  main.cpp
//  aread
//
//  Created by Diana Melnick on 21.05.2019.
//  Copyright © 2019 Diana Melnick. All rights reserved.
//
#include <stdio.h>
#include <cstdio>
#include <iostream>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <vector>
#include <unistd.h>
#include <sys/ipc.h>
#include <ctime>
#include <sys/sem.h>
#include "semaphore.h"
#include <sys/file.h>
#include <sys/types.h>
#include <sys/errno.h>
#include <aio.h>
using namespace std;
#define TNAME "aio_read/5-1.c"

int asincro_read(aiocb aiocb, int fd)
{
    if (aio_read(&aiocb) == -1) {
        printf(TNAME " Error at aio_read(): %s\n",
               strerror(errno));
        close(fd);
        exit(2);
    }
    
    int err=aio_error(&aiocb);
    while ((err = aio_error (&aiocb)) == EINPROGRESS);
    int ret=aio_return(&aiocb);
    if (ret < 0) {
        printf(TNAME " Error at aio_return()\n");
        close(fd);
        exit(2);
    }
    return ret;
}
