#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <pthread.h>
#include <vector>
#include <unistd.h>
#include <ctime>

using namespace std;
pthread_mutex_t my_mutex;

void menu();



void* atomicOutput(void *args) {
    clock_t numb= clock()/100;
    
        while(1){
            sleep(1);
            pthread_mutex_lock(&my_mutex);
            std::string str = "" + std::to_string(numb);
            for (auto &c:str) cout<< c;
            cout<<endl;
            pthread_mutex_unlock(&my_mutex);
        }
    return 0;
}


int main()
{
    //MUTEX
    int tmp;
    tmp=pthread_mutex_init(&my_mutex, NULL);
    
    //THREADS
    pthread_t thread;
    int status;
    std::vector<pthread_t> childs={};
    
    //MENU
    menu();
    
    //BUFFER&INPUT
    char cmd[2];
    bool exit = false;
    while(!exit){
        bool readed = false;
        if (read(STDIN_FILENO, &cmd, 2) < 0){
            if (errno != EAGAIN){
                perror("read failed:");
                pthread_mutex_destroy(&my_mutex);
                return errno;
            }
        }else{
            readed = true;
        }
        if (readed)
            switch (cmd[0]){ /*cmd[1] is a newline*/
                case '+':
                    status = pthread_create(&thread, NULL, atomicOutput, NULL);
                    if (status != 0) {
                        printf("main error: can't create thread, status = %d\n", status);
                        pthread_mutex_destroy(&my_mutex);
                        return 88;
                    }
                    childs.push_back(thread);
                    break;
                    
                case'-':
                    pthread_cancel(*(childs.end()-1));
                    childs.pop_back();
                    break;
                    
                case 'q':
                    childs.clear();
                    exit = true;
                    break;
            }
    }
    pthread_mutex_destroy(&my_mutex);
    return 0;
}

void menu()
{
    cout << endl << "\t\t\tWhat do u want to do?" << endl;
    cout << "\t\t\t'+' - to create process" << endl;
    cout << "\t\t\t'-' - to stop process" << endl;
    cout << "\t\t\t's' - to start process" << endl;
    cout << "\t\t\t'q' - to quite" << endl;
    return;
}


