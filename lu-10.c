#include <stdio.h>
#include <stdlib.h>

int main(){
    int bitmap_size = 0;
    printf("Enter bitmap size: ");
    scanf("%d", &bitmap_size);
    printf("Memory required :");
    int memory_req;
    scanf("%d", &memory_req);
    int *bitmap = (int*)malloc(sizeof(int)*bitmap_size);
    for(int i = 0; i < bitmap_size; i++){
        bitmap[i] = rand()%10;
    }
    int start_indx = 0;
    int end_indx = 0;
    int count=0;
    for (int i = 0; i < bitmap_size; i++)
    {
        printf("\n%d->", bitmap[i]);
        for (int j = 7; j >= 0; j--)
        {
            printf("%d", (bitmap[i] >> j) & 1);
            if(((bitmap[i]>>j)&1)==1){count =0;start_indx = i*8+j;}
            else {count++;} 
            if(count == memory_req){end_indx = i*8+j+1;goto quit;}
        }

    }
    quit:
    printf("\nStart index: %d\nEnd index: %d", start_indx, end_indx);
}