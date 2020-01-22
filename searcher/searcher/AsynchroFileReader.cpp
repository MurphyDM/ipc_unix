//
//  AsynchroFileReader.cpp
//  searcher
//
//  Created by Diana Melnick on 01.06.2019.
//  Copyright © 2019 Diana Melnick. All rights reserved.
//

#include "AsynchroFileReader.hpp"

AsynchroFileReader :: AsynchroFileReader(vector<char*>files, int size){
    this->files=files;
    this->size=size;
}

aiocb AsynchroFileReader:: aiocbIniz(int fd, char *pathname, long long size)
{
    aiocb aiocb;
    memset(&aiocb, 0, sizeof(struct aiocb));
    aiocb.aio_fildes = fd;
    aiocb.aio_buf = pathname;
    aiocb.aio_nbytes = size;
    return aiocb;
}

int AsynchroFileReader:: asyncroWrite(aiocb aiocb, int fd)
{
    if (aio_write(&aiocb) == -1) {
        printf(TNAME " Error at aio_write(): %s\n", strerror(errno));
        exit(2);
    }
    
    
    int err = aio_error(&aiocb);
    while ((err = aio_error (&aiocb)) == EINPROGRESS);
    
    int ret=aio_return(&aiocb);
    if (ret < 0) {
        printf(TNAME " Error at aio_return()\n");
        close(fd);
        exit(2);
    }
    return ret;
}

int AsynchroFileReader:: asincroRead(aiocb aiocb, int fd)
{
    if (aio_read(&aiocb) == -1) {
        printf(TNAME " Error at aio_read(): %s\n",
               strerror(errno));
        close(fd);
        exit(2);
    }
    
    int err=aio_error(&aiocb);
    while ((err = aio_error (&aiocb)) == EINPROGRESS);
    int ret = aio_return(&aiocb);
    if (ret < 0) {
        printf(TNAME " Error at aio_return()\n");
        close(fd);
        exit(2);
    }
    return ret;
}

int AsynchroFileReader:: openFile(char *fileName)
{
    int fd = open(fileName, O_RDWR | O_NONBLOCK);
    if (fd < 0) {
        perror("open error! HERE YOU ARE!!!");
        return -1;
    }
    return fd;
}

int AsynchroFileReader:: readIt()
{
    int pipe;
    PipeCreator pipeCreator;
    pipeCreator.createFIFO(NAME);
    
    char *pre_buffer;
    pre_buffer = (char*)calloc(SIZE, sizeof(char));
    
    int perms= IPC_CREAT|IPC_EXCL|SEM_A|SEM_R;
    int semid = semget(key, 1, perms);
    semctl(semid, 0, SETVAL, 0);
    
    for (int i=0; i<size; i++)
    {
        int fd = openFile(files[i]);
        
        aiocb aiocb= aiocbIniz(fd, pre_buffer, SIZE);
        
        while(1)
        {
            memset(pre_buffer, ' ', SIZE);
            createThread();
            int ret=asincroRead(aiocb, fd);
            aiocb.aio_offset= aiocb.aio_offset + ret;
            pipe = pipeCreator.openFIFO(O_WRONLY, NAME);
            pipeCreator.writeTo(pipe, pre_buffer, SIZE);
            semctl(semid, 0, SETVAL, 1);
            while(semctl(semid, 0, GETVAL, 0)!=0);
            close(pipe);
            
            if(ret<SIZE){ break; }
        }
        
        close(fd);
    }
    int res= semctl(semid, 0, IPC_RMID); //удаление семафорчика
    if (res!=-1) cout<<endl<<"smphore is del"<<endl;
    return 0;
}

