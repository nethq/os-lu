#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

typedef struct thread{
    unsigned index;
    HANDLE handle;
    DWORD cpu_id;
}thread;

HANDLE mutex1;
HANDLE temp;
int count_overwritten_handles_during_work=0;

DWORD WINAPI thread_funcion(void *p)
{
    thread *x  = (thread*) p;
    printf("\n{%d}[%d] started!",x->index,x->cpu_id);
    WaitForSingleObject(mutex1,INFINITE);
    for(int i =0;i<1000000;i++){temp = x->handle;
    if(temp!=x->handle) count_overwritten_handles_during_work++;}
    ReleaseMutex(mutex1); 
    printf("\n{%d}[%d] terminated!",x->index,x->cpu_id);   
}

int main(){
    printf("Thread count :");
    int thread_count=0;
    scanf("%d",&thread_count);

    thread * arr_thrds = (thread*)malloc(sizeof(thread)*thread_count);
    mutex1 = CreateMutex(NULL,0,mutex1);
    for (int i = 0; i < thread_count; i++)
    {
        arr_thrds[i].index = i;
        arr_thrds[i].handle = CreateThread(NULL,0,thread_funcion,arr_thrds+i,CREATE_SUSPENDED,&arr_thrds[i].cpu_id);
    }
    for (int i = 0; i < thread_count; i++)
    {
        ResumeThread(arr_thrds[i].handle);
    }
    
    for (int i = 0; i < thread_count; i++)
    {
        WaitForSingleObject(arr_thrds[i].handle,INFINITE);//waiting for all threads sequentially 
    }
    
    printf("Count of how many threads's handles were overwritten on the global resource while one thread was writing. %d \n",count_overwritten_handles_during_work);
    printf("Main thread terminated!");
    
}