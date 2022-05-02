// 190001058
// Somya Mehta
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int n;

long long int *arr;//  array for storing the fibonacci series

// this is the worker function for the task that thread has to perform
void *fib_Func(void *arg)
{
	arr[0] = 0;
	arr[1] = 1;
	for (int i = 2; i < n; i++)
	{
		arr[i] = arr[i - 1] + arr[i - 2];
	}
	return NULL;
}
void printArray(){
	printf("%d elements of fibonacci are: ", n);
    for (int i = 0; i < n; i++)
	{
		printf("%lld ", arr[i]);
		if(i!=0&&i%10==0)printf("\n");
	}
	printf("\n");
}
int main()
{
	printf("Enter total number of elements you want in the fibonacci series: ");
	scanf("%d", &n);
	pthread_t id;//pthread object
	arr = (long long int *)malloc(n * sizeof(long long int));// dynamically allocating the memory for the array of size n
	pthread_create(&id, NULL, fib_Func, &n);//to create child thread
	pthread_join(id, NULL);//to join child thread
    printArray();
}