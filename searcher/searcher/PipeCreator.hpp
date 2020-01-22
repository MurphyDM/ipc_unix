//
//  PipeCreator.hpp
//  searcher
//
//  Created by Diana Melnick on 01.06.2019.
//  Copyright © 2019 Diana Melnick. All rights reserved.
//

#ifndef PipeCreator_hpp
#define PipeCreator_hpp

#include <stdio.h>
#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <ctime>
#include <sys/sem.h>
#include "semaphore.h"
#include <sys/file.h>
#include <sys/types.h>
#include <sys/errno.h>
#include <aio.h>
#include <signal.h>
#include <sys/wait.h>
#include <vector>
#include <limits.h>
#include <sys/stat.h>
#include <dirent.h>
#include "ThreadCreator.hpp"


class PipeCreator
{
public:
    char* readFrom(int pipe, char * buffer, long long size);
    
    void writeTo(int pipe, char *buffer, long long size);
    
    void createFIFO(char *name);
    
    int openFIFO(int open_mode, char *name);
};
#endif /* PipeCreator_hpp */

