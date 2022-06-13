#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define handle HANDLE
#define buff_SIZE 100
typedef struct thread{
    unsigned index;
    HANDLE handle;
    DWORD cpu_id;
}thread;

handle semaphore;
int *buff;
DWORD WINAPI thread_producer_funcion(void *p)
{
    thread *x  = (thread*) p;
    printf("\nProducer {%d}[%d] started!",x->index,x->cpu_id);
    while(1<2)
    {   
        Sleep(1000);
        for(int i =0;i<buff_SIZE;i++)
        {   
            if(buff[i]==0){
                buff[i]=rand()%buff_SIZE;
                ReleaseSemaphore(semaphore,1,NULL);
                printf("\n[Pr_ID -> %d] = 0 -> %d",x->index,buff[i]);
            }
        }    
    }
    printf("\nProducer {%d}[%d] terminated!",x->index,x->cpu_id);   
}

DWORD WINAPI thread_consumer_funuction(void *p)
{
    thread *x  = (thread*) p;
    printf("\nConsumer {%d}[%d] started!",x->index,x->cpu_id);
    while(1<2)
    {
        Sleep(1000);
        WaitForSingleObject(semaphore,INFINITE);
        for(int i =0;i<buff_SIZE;i++){
            if(buff[i] != 0) {printf("\n[Cons->%d] changed buff[%d]->0",x->index,buff[i]);
            buff[i]=0;
           }
        }
    }
    printf("\nConsumer {%d}[%d] terminated!",x->index,x->cpu_id);   

}

int main(){
    printf("Thread producer count :");
    int thread_prod_count=0,thread_cons_count=0;
    scanf("%d",&thread_prod_count);
    printf("Thread consumer count : ");
    scanf("%d",&thread_cons_count);

    thread *arr_prod = (thread *)malloc(sizeof(thread)*thread_prod_count);
    thread *arr_cons = (thread *)malloc(sizeof(thread)*thread_cons_count);
    buff = (int*) calloc(buff_SIZE,sizeof(int));

    semaphore = CreateSemaphore(NULL,0,buff_SIZE,semaphore);
    
    for (int i = 0; i < thread_prod_count; i++)
    {
        arr_prod[i].index = i;
        arr_prod[i].handle = CreateThread(NULL,0,thread_producer_funcion,arr_prod+i,CREATE_SUSPENDED,&arr_prod[i].cpu_id);
    }
    for (int i = 0; i < thread_cons_count; i++)
    {
        arr_cons[i].index = i;
        arr_cons[i].handle = CreateThread(NULL,0,thread_consumer_funuction,arr_cons+i,CREATE_SUSPENDED,&arr_cons[i].cpu_id);
    }
    
    for (int i = 0; i < thread_cons_count; i++)
    {
        ResumeThread(arr_cons[i].HANDLE);
    }
    for (int i = 0; i < thread_prod_count; i++)
    {
        ResumeThread(arr_prod[i].HANDLE);
    }

    fflush(stdin);
    int d;
    fflush(stdin);
    scanf("%d",&d);
    for (int i = 0; i < thread_cons_count; i++)
    {
        TerminateJobObject(arr_cons[i].HANDLE,0);
        printf("\nTerminating consumer thread{%d}[%d]",arr_cons[i].index,arr_cons[i].cpu_id);
    }
    for (int i = 0; i < thread_prod_count; i++)
    {
        TerminateJobObject(arr_prod[i].HANDLE,0);
        printf("\nTerminating producer thread{%d}[%d]",arr_prod[i].index,arr_prod[i].cpu_id);
    }
    
    system("PAUSE");
    printf("\nMain thread terminated!");
    
}