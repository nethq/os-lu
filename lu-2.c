#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct student{
    int fnum;
    char name[20];
    float grade;
}student;

void randFill(student *arr,int size)
{
    int i;
    for(i=0;i<size;i++)
    {
        arr[i].fnum=rand()%100;
        arr[i].grade=rand()%6;
        strcpy(arr[i].name,"<name>");
    }
}

int main(){
    int n;
    printf("Number of students?");	// prompt user for number of students
    scanf("%d",&n);			// read number of students	
    student *s = (student*)malloc(sizeof(student)*n);
    randFill(s,n);

    for (int i = 0; i < n; i++)
    {
        printf("\nStudent %d : %d %s %f",i,s[i].fnum,s[i].name,s[i].grade);
    }
    
    return 0;
}