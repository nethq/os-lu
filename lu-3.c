//Работа с нишки. Създаване на нишки. Особености на main функцията.
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

struct threadinfo{
unsigned index; // индекс на нишката по реда на създаване
HANDLE h; // handle (манипулатор) на нишката
DWORD tid; // tid на нишката
};

DWORD WINAPI thread_func(void *p)
{
    struct threadinfo *x = (struct threadinfo*) p;
    printf("\nThread %d[CPU-ID:%d] started!",x->index,x->tid);
    for (int i = 0; i < 1000000; i++)
    {
        
    }
    printf("\nThread %d[CPU-ID:%d] terminated!",x->index,x->tid);
    return 0;
}

int main(){

    int n;
    printf("Number of threads?");	// prompt user for number of threads
    scanf("%d",&n);			// read number of threads
    struct threadinfo *threads = (struct threadinfo*)malloc(sizeof(struct threadinfo)*n);
    HANDLE *arr = (HANDLE*) malloc(sizeof(HANDLE)*n);

    for(int i =0;i<n;i++)
    {
        threads[i].index = i;
        threads[i].h = CreateThread(NULL,0,thread_func,threads+i,CREATE_SUSPENDED,&threads[i].tid);
        arr[i] = threads[i].h;    
    }
    for (int i = 0; i < n; i++)
    {
        ResumeThread(threads[i].h);
    }
    WaitForMultipleObjects(n,arr,1,INFINITE);
    printf("\nMain func terminating...");
    system("PAUSE");
    return 0;

}