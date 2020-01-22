

#include "AsynchroFileReader.hpp"

int sendmail(const char *to, const char *from, const char *subject, const char *message);
void* readMessage(void *args);

void createThread()
{
    //THREADS
    pthread_t thread;
    int status = pthread_create(&thread, NULL, readMessage, NULL);
    if (status != 0) {
        printf("main error: can't create thread, status = %d\n", status);
    }
}

void* readMessage(void *args) {
    PipeCreator pc;
    int perms= SEM_A|SEM_R;
    int semid = semget(key, 1, perms);
    int pipe = pc.openFIFO(O_RDONLY|O_NONBLOCK, NAME);
    while((semctl(semid, 0, GETVAL)!=1));
    
    char* buffer;
    buffer=(char*)calloc(SIZE, sizeof(char));
    pc.readFrom(pipe, buffer, SIZE);
    
    sendmail("Testsearcher@yandex.by","mymac", "list", buffer);
    cout<<endl<<"Result file is SEND"<<endl;
    semctl(semid, 0, SETVAL, 0);
    return 0;
}


int sendmail(const char *to, const char *from, const char *subject, const char *message)
{
    int retval = -1;
    FILE *mailpipe = popen("/usr/sbin/sendmail -t", "w");
    if (mailpipe != NULL) {
        fprintf(mailpipe, "To: %s\n", to);
        fprintf(mailpipe, "From: %s\n", from);
        fprintf(mailpipe, "Subject: %s\n\n", subject);
        fwrite(message, 1, strlen(message), mailpipe);
        fwrite(".\n", 1, 2, mailpipe);
        pclose(mailpipe);
        retval = 0;
    }
    else {
        perror("Failed to invoke sendmail");
    }
    return retval;
}

