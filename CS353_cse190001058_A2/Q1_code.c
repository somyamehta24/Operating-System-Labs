//Somya Mehta
// 190001058

#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
int cmp (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

//for merging two sorted halves of the array
void merge_function(int array[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int left[n1], right[n2];
    for (i = 0; i < n1; i++)
        left[i] = array[l + i];
    for (j = 0; j < n2; j++)
        right[j] = array[m + 1 + j];

    i = 0; 
    j = 0; 
    k = l;
    while (i < n1 && j < n2) {
        if (left[i] <= right[j]) {
            array[k] = left[i];
            i++;
        }
        else {
            array[k] = right[j];
            j++;
        }
        k++;
    }
  
    while (i < n1) {
        array[k] = left[i];
        i++;
        k++;
    }
  
    while (j < n2) {
        array[k] = right[j];
        j++;
        k++;
    }
}

void swap(int* a, int* b) 
{ 
    int t = *a; 
    *a = *b; 
    *b = t; 
}  
int main(){
    int shmid;
    key_t k = 5668;
    int *array;
    //creating shared memory
    shmid = shmget(k, 10*sizeof(int), 0666 | IPC_CREAT); 
    //for attaching array to shared memory
    array = shmat(shmid, NULL, 0);
    printf("Enter 10 elements of the array in any order: ");
    for(int i=0; i<10; i++){
    	scanf("%d",&array[i]);
    }
    // creating the first child process 
    int child1=fork(); 
    if(child1==0){
        //quickSort_function(array,0,4);
        
        qsort(array,5,sizeof(int),cmp);
        // detaching child process 1 from shared memory
    	shmdt(array); 
    }
    else{
        // creating second child process
    	int child2=fork(); 
    	if(child2==0){
    	        qsort(array+5,5,sizeof(int),cmp);
    	    // detaching child process 2 from shared memory
    	    shmdt(array); 
        }
        else{
            //waiting for child processes to finish
            waitpid(child1, NULL, 0);
            waitpid(child2, NULL, 0);
            // merging the two halves of array
            merge_function(array, 0, 4, 9); 
            // printing sorted array
            printf("Final array after sorting: ");
            for(int i=0; i<10; i++){
                printf("%d ",array[i]);
            }
            // detaching parent process from shared memory
            shmdt(array); 
            // deleting shared memory
            shmctl(shmid, IPC_RMID, 0); 
        }
    }
}
