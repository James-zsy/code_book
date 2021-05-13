#include <iostream> 
#include <pthread.h> 
#include <stdlib.h> 
#include <unistd.h> 
 
using namespace std; 
pthread_cond_t qready = PTHREAD_COND_INITIALIZER;    /*初始构造条件变量*/ 
pthread_mutex_t qlock = PTHREAD_MUTEX_INITIALIZER;    /*初始构造锁*/ 
int x = 10; 
int y = 20; 
void *func0(void *arg){ 
    double i = 0; 
        while(1){ 
        cout<<"                        time stamp : "<< 0.2 * i++ <<endl; 
        usleep(200*1000); 
    } 
} 
void *func1(void *arg){ 
        cout<<"func1 start"<<endl; 
    pthread_mutex_lock(&qlock); 
    while(x<y) 
    { 
        pthread_cond_wait(&qready,&qlock); 
    } 
        cout<<"func1 running"<<endl; 
        sleep(1); 
    pthread_mutex_unlock(&qlock); 
    //sleep(3); 
        cout<<"func1 end"<<endl; 
} 
void *func2(void *arg){ 
        cout<<"func2 start"<<endl; 
    sleep(5); 
    pthread_mutex_lock(&qlock); 
    x = 20; 
    y = 10; 
    cout<<"has change x and y"<<endl; 
    pthread_mutex_unlock(&qlock); 
    if(x > y){ 
        pthread_cond_signal(&qready); 
    } 
    cout<<"func2 end"<<endl; 
} 
 
void *func3(void *arg){ 
        cout<<"func3 start"<<endl; 
    pthread_mutex_lock(&qlock); 
        cout<<"func3 running"<<endl; 
        sleep(5); 
    pthread_mutex_unlock(&qlock); 
    sleep(1); 
        cout<<"func3 end"<<endl; 
} 
 
int main(int argc,char **argv){ 
        pthread_t tid0,tid1,tid2,tid3; 
    int iRet; 
    iRet = pthread_create(&tid0,NULL,func0,NULL); 
    if(iRet){ 
        cout<<"pthread 1 create error"<<endl; 
                return iRet; 
    } 
    iRet = pthread_create(&tid1,NULL,func1,NULL); 
    if(iRet){ 
        cout<<"pthread 1 create error"<<endl; 
                return iRet; 
    } 
        sleep(2); 
    iRet = pthread_create(&tid2,NULL,func2,NULL); 
    if(iRet){ 
        cout<<"pthread 2 create error"<<endl; 
                return iRet; 
    } 
        sleep(2); 
    iRet = pthread_create(&tid3,NULL,func3,NULL); 
    if(iRet){ 
        cout<<"pthread 2 create error"<<endl; 
                return iRet; 
    } 
    sleep(20);     
    cout<<"test over"<<endl; 
    return 0;     
} 
