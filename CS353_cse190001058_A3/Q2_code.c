// 190001058
// Somya Mehta

#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define SIZE 10
int a[SIZE];
//User Input
void takeInput(){

    printf("Enter 10 elements of the array: ");
    for(int i=0;i<SIZE;i++){
        int x;
        scanf("%d",&x);
        a[i]=x;
    }
    printf("\n");
}
//comparator for qsort
int comparator(const void* p,const void* q){
    int l=*((int*)p),r=*((int*)q);
    return l-r;
}

// function executed by the threads
void* func(void* ptr){
    qsort(ptr,SIZE/2,sizeof(int),comparator);
}

//merge the Arrays
void merge(int* a){
    int i=0,j=SIZE/2,k=0;
    int temp[SIZE];
    while(i!=SIZE/2 && j!=SIZE){
        if(a[i]>=a[j]){
            temp[k++]=a[j++];
        }else{
            temp[k++]=a[i++];
        }
    }
    while(j!=SIZE){
        temp[k++]=a[j++];
    }
    while(i!=SIZE/2){
        temp[k++]=a[i++];
    }
    for(int i=0;i<SIZE;i++){
        a[i]=temp[i];
    }
}

//print the array
void printArray(){
	printf("%d elements of Sorted Array are: ", 10);
    for (int i = 0; i < 10; i++)
	{
		printf("%d ", a[i]);
	}
    printf("\n");
}

int main(){
    
    takeInput();

    // creating two threads
    pthread_t tid1,tid2;
    pthread_create(&tid1,NULL,func,(void*)(a));//thread 1 sorts half array
    pthread_create(&tid2,NULL,func,(void*)(a+SIZE/2));//thread 2 sorts remaining half array

    //joining the two threads
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    
    merge(a);
    printArray();
}