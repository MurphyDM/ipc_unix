//
//  MainlSender.hpp
//  searcher
//
//  Created by Diana Melnick on 01.06.2019.
//  Copyright © 2019 Diana Melnick. All rights reserved.
//

#ifndef MainlSender_hpp
#define MainlSender_hpp

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
using namespace std;
#define key 134
#define TNAME "aio_read/5-1.c"
#define NAME "/tmp/fif"
#define SIZE 5000

class MailSender{
public:
   
};

#endif /* MainlSender_hpp */
