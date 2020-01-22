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
#include <limits.h>
#include <sys/stat.h>
#include <dirent.h>

#define SIZE 18
#define key 139
#define TNAME "aio_read/5-1.c"
#define NAME "/tmp/fifo"
using namespace std;

void write_to(int pipe, char *buffer, long size);
char* read_from(int pipe, char * buffer);
void create_fifo();
void create_thread();
int create_sem(int perms);
extern int asincro_read(aiocb aiocb, int fd);
extern int asyncro_write(aiocb aiocb, int fd);


void* write_it(void *args) {
    int perms= SEM_A|SEM_R;
    int semid = semget(key, 1, perms);
    
    int pipe;
    int open_mode = O_RDONLY|O_NONBLOCK;
  
    cout<<"0";
    pipe = open(NAME, open_mode);
    cout<<"1";
    while((semctl(semid, 0, GETVAL)!=1));
    
    char* buffer;
    buffer=(char*)calloc(SIZE, sizeof(char));
    read_from(pipe, buffer);
    cout<<"2";
    
    int fd = open("/Users/Diana/Documents/exam2/ASM/Lab5-FILES/resut.txt", O_WRONLY|O_CREAT|O_APPEND);
    if (fd < 0)
    { perror("open error"); return 0; }
    
    
    aiocb aiocb;
    memset(&aiocb, 0, sizeof(struct aiocb));
    aiocb.aio_fildes = fd;
    aiocb.aio_buf = buffer;
    aiocb.aio_nbytes = SIZE;///!!!

    int ret = asyncro_write(aiocb, fd);
   
    cout<<endl<<"Result file is ready"<<endl;

    semctl(semid, 0, SETVAL, 0);
    close(fd);
    return 0;
}


int read_it(char* pathName)
//int main()
{
    int pipe;
    int open_mode = O_WRONLY;
    create_fifo();
    
    char *pre_buffer;
    pre_buffer = (char*)calloc(SIZE, sizeof(char));
    
   // char filename[]="/users/diana/documents/exam2/asm/lab5-files/direct/init.txt";
    int perms= IPC_CREAT|IPC_EXCL|SEM_A|SEM_R;
    int semid = semget(key, 1, perms);
    semctl(semid, 0, SETVAL, 0);
    
    int fd = open(pathName, O_RDWR | O_NONBLOCK);
    if (fd < 0) {
        perror("open error! HERE YOU ARE");
        return -1;
    }
    
    aiocb aiocb;
    memset(&aiocb, 0, sizeof(struct aiocb));
    aiocb.aio_fildes = fd;
    aiocb.aio_buf = pre_buffer;
    aiocb.aio_nbytes = SIZE;
    
 while(1)
 {
    memset(pre_buffer, ' ', SIZE);

    create_thread();
    int ret=asincro_read(aiocb, fd);
    aiocb.aio_offset= aiocb.aio_offset + ret;
    

    pipe = open(NAME, open_mode);
    printf("Process %d result %d \n", getpid(), pipe);
    write_to(pipe, pre_buffer, ret);
    
    //func(pre_buffer);
    /*for (int i = 0; i < ret; i++)
        cout<<pre_buffer[i];*/
     
   
     semctl(semid, 0, SETVAL, 1);
     while(semctl(semid, 0, GETVAL, 0)!=0);
    close(pipe);
     
     if(ret<SIZE){ break; }
 }
    
    close(fd);
    int res= semctl(semid, 0, IPC_RMID); //удаление семафорчика
    if (res!=-1) cout<<endl<<"smphore is del"<<endl;
    return 0;
}




//;*******************************open_dir********************************

int main(int argc, char *argv[])
{
    char theDir[]="/users/diana/documents/exam2/asm/lab5-files/direct";
    DIR *dir = NULL;
    struct dirent entry;
    struct dirent *entryPtr = NULL;
    int retval = 0;
    unsigned count = 0;
    char pathName[PATH_MAX + 1];
    
    // открыть указанный каталог, если возможно.
    dir = opendir( theDir );
    if( dir == NULL ) {
        printf( "Error opening %s: %s", theDir, strerror( errno ) );
        return 0;
    }
    
    retval = readdir_r( dir, &entry, &entryPtr );
    
    while( entryPtr != NULL ) {
        
        struct stat entryInfo;
        
        if( ( strncmp( entry.d_name, ".", PATH_MAX ) == 0 ) ||
           ( strncmp( entry.d_name, "..", PATH_MAX ) == 0 ) ) {
            retval = readdir_r( dir, &entry, &entryPtr );
            continue; }
        
        (void)strncpy( pathName, theDir, PATH_MAX );
        (void)strncat( pathName, "/", PATH_MAX );
        (void)strncat( pathName, entry.d_name, PATH_MAX );
        
        if( lstat( pathName, &entryInfo ) == 0 ) {
            // вызов stat() был успешным, так что продолжаем.
            count++;
            
          if( S_ISREG( entryInfo.st_mode ) ) { //mac
                // обычный файл
                printf( "\t%s has %lld bytes\n", pathName, (long long)entryInfo.st_size );
                read_it(pathName);
          }
        }
        else {
            printf( "Error statting %s: %s\n", pathName, strerror( errno ) );
        }
        retval = readdir_r( dir, &entry, &entryPtr );
    }
    // закрытие каталога и возвращение числа элементов.
    (void)closedir( dir );
    return count;
}


//******************************functions*********************************


void create_thread()
{
    //THREADS
    pthread_t thread;
    int status = pthread_create(&thread, NULL, write_it, NULL);
    if (status != 0) {
        printf("main error: can't create thread, status = %d\n", status);
    }
    
}


void write_to(int pipe, char *buffer, long size)
{
    int fifo;
    if (pipe != -1)
    {
        fifo = write(pipe, buffer, SIZE);
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

char* read_from(int pipe, char * buffer)
{
    int res;
    if (pipe != -1)
    {
        res = read(pipe, buffer, SIZE);
        (void)close(pipe);
    }
    else
    {
        exit(EXIT_FAILURE);
    }
    return buffer;
}

void create_fifo()
{
    int fifo;
    if (access(NAME, F_OK) == -1) //exisr test
    {
        fifo = mkfifo(NAME, 0777);
        if (fifo != 0)
        {
            fprintf(stderr, "Could not create fifo %s \n", NAME);
            exit(EXIT_FAILURE);
        }
    }
}






























/*int asyncro_write(aiocb aiocb, int fd)
{
    if (aio_write(&aiocb) == -1) {
        printf(TNAME " Error at aio_write(): %s\n", strerror(errno));
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
    int ret = aio_return(&aiocb);
    if (ret < 0) {
        printf(TNAME " Error at aio_return()\n");
        close(fd);
        exit(2);
    }
    return ret;
}
*/




