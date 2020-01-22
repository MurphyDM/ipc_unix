//
//  AsynchroFileReader.hpp
//  searcher
//
//  Created by Diana Melnick on 01.06.2019.
//  Copyright © 2019 Diana Melnick. All rights reserved.
//
//
#ifndef AsynchroFileReader_hpp
#define AsynchroFileReader_hpp

#include <iostream>
#include <stdio.h>
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
#include "PipeCreator.hpp"
#include "FileCreator.hpp"
#define key 178
#define TNAME "aio_read/5-1.c"
#define NAME "/tmp/fifo"
#define SIZE 8000
using namespace std;

int sendmail(const char *to, const char *from, const char *subject, const char *message);
char* read_from(int pipe, char * buffer, long long size);
void* readMessage(void *args);
void createThread();


class AsynchroFileReader{
    
private:
    vector<char*> files;
    int size;
public:
    
    AsynchroFileReader(vector<char*> files, int size);
    
    aiocb aiocbIniz(int fd, char *pathname, long long size);
    
    int asyncroWrite(aiocb aiocb, int fd);
    
    int asincroRead(aiocb aiocb, int fd);
    
    int openFile(char *fileName);
    
    int readIt();
    
};


#endif /* AsynchroFileReader_hpp */


