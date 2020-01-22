//
//  PipeCreator.cpp
//  searcher
//
//  Created by Diana Melnick on 01.06.2019.
//  Copyright © 2019 Diana Melnick. All rights reserved.
//

#include "PipeCreator.hpp"
char* PipeCreator:: readFrom(int pipe, char * buffer, long long size)
{
    int res;
    if (pipe != -1)
    {
        res = read(pipe, buffer, size);
        (void)close(pipe);
    }
    else
    {
        exit(EXIT_FAILURE);
    }
    return buffer;
}

void PipeCreator:: writeTo(int pipe, char *buffer, long long size)
{
    int fifo;
    if (pipe != -1)
    {
        fifo = write(pipe, buffer, size);
        if (fifo == -1)
        {
            fprintf(stderr, "Write error on pipe \n");
            exit(EXIT_FAILURE);
        }
        (void)close(pipe);
    }
    else
    {
        exit(EXIT_FAILURE);
        
    }
}

void PipeCreator:: createFIFO(char *name)
{
    int fifo;
    if (access(name, F_OK) == -1) //exisr test
    {
        fifo = mkfifo(name, 0777);
        if (fifo != 0)
        {
            fprintf(stderr, "Could not create fifo %s \n", name);
            exit(EXIT_FAILURE);
        }
    }
}

int PipeCreator:: openFIFO(int open_mode, char *name)
{
    int pipe = open(name, open_mode);
    return pipe;
}

