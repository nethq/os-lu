#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

typedef struct thread_l{
    unsigned indx_l;
    HANDLE h;
    DWORD tid;
    int start_indx,end_indx,sum;
}thread_l;

int *arr;
LARGE_INTEGER start_time,stop_time;

DWORD WINAPI thread_function(void *p){

    thread_l *x = (thread_l*) p;
    //printf("\nThread {ID=%d}[CPU_ID=%d] started! Working on [%d : %d]",x->indx_l,x->tid,x->start_indx,x->end_indx);
    for(int i =x->start_indx; i<x->end_indx;i++)
    {
        x->sum+=arr[i];
    }
    QueryPerformanceCounter(&stop_time);
    //printf("\nThread {ID=%d}[CPU_ID=%d] terminated with : sum = %d",x->indx_l,x->tid,x->sum);
}

int main(){
    fprintf(stdout,"Thread count:");
    int n=0,l=0;
    fscanf(stdin,"%d",&n);
    fprintf(stdout,"Array lenght:");
    fscanf(stdin,"%d",&l);
    
    thread_l *a  = (thread_l*) malloc(sizeof(thread_l)*n);
    arr = (int*)malloc(sizeof(int)*l);


    int work_size=l/n;//lenght of array / count of threads
    
    HANDLE * handles = (HANDLE*)malloc(sizeof(HANDLE)*n);

    for(int i =0;i<l;i++){arr[i]=1;}
    for (int i = 0; i < n; i++){
        a[i].start_indx=i*work_size;
        a[i].end_indx = a[i].start_indx+work_size;
        a[i].indx_l = i;
        a[i].h = CreateThread(NULL,0,thread_function,a+i,CREATE_SUSPENDED,&a[i].tid);
        if(i==n-1)
        {
            a[i].end_indx=l;
        }
        handles[i] = a[i].h;
        a[i].sum=0;
    }
    QueryPerformanceCounter(&start_time);
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    for (int i = 0; i < n; i++)
    {
        ResumeThread(a[i].h);
    }
    unsigned int total_sum = 0; 
    for(int i =0 ; i<n;i++){
    WaitForSingleObject(handles[i],INFINITE);
    total_sum+=a[i].sum;
    }
    
    LARGE_INTEGER syncronous_start_time,syncronous_stop_time;
    QueryPerformanceCounter(&syncronous_start_time);
    int sum=0;
    for(int i =0;i<l;i++){sum+=arr[i];}
    QueryPerformanceCounter(&syncronous_stop_time);
    printf("\nTotal sum  = %d",total_sum);
    printf("\nExec time with async : %f",(double)(stop_time.QuadPart-start_time.QuadPart)/freq.QuadPart);
    printf("\nExec time with sync : %f",(double)(syncronous_stop_time.QuadPart-syncronous_start_time.QuadPart)/freq.QuadPart);
    printf("\nMain func terminated");
    return 0; 
}

