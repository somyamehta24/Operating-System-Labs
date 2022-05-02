// Somya Mehta
// 190001058

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    key_t key = 100;
    int siz = sizeof(int);
    int pid_of_process_A, pid_of_process_B;
    int *X = NULL;
    int shmid = shmget(key, siz, IPC_CREAT | 0666);  // creating shared memory

    // Unsynchronised problem
    if (shmid >= 0)  // check if memory is allocated
    {
        X = shmat(shmid, NULL, 0);  // attaching memory to parent process
        if (X != (int *)(-1))       // check if shared memory attachment successful
        {
            *X = 0;                     // Initialize shared variable to 0
            pid_of_process_A = fork();  // Now we Fork two times to make two child processes
            if (pid_of_process_A > 0)   // for parent process
            {
                pid_of_process_B = fork();  // Fork again to create process B
                if (pid_of_process_B == 0)  // process B
                {
                    // Attach the process to shared memory
                    int *X_in_b = shmat(shmid, NULL, 0);
                    if (X_in_b != (int *)(-1))  // check if Shared memory attachment successful for b
                    {
                        // Increment shared variable for 100000 times
                        for (int i = 1; i <= 100000; i++) {
                            (*X_in_b) = (*X_in_b) - 1;
                        }
                        shmdt(X_in_b);  // Detach from shared memory
                    } else {
                        printf("\nError while attaching memory to process A");  // Shared memory attachment for Process B is unsuccessful
                    }
                }
            } else {
                // process  A
                int *X_in_a = shmat(shmid, NULL, 0);  // Attach process a to shared memory
                if (X_in_a != (int *)(-1))            // check if Shared memory attachment successful for a
                {
                    // Increment shared variable for 100000 times
                    for (int i = 1; i <= 100000; i++) (*X_in_a) = (*X_in_a) + 1;

                    shmdt(X_in_a);  // Detach process a from shared memory
                } else {
                    printf("\nError while attaching memory to process A");
                }
            }
        } else {
            printf("\nError while attaching memory to parent");
        }
    } else {
        printf("\nError in allocation");  // if memory allocation fails
    }

    // Waiting for children to complete
    int status;
    waitpid(pid_of_process_A, &status, 0);
    waitpid(pid_of_process_B, &status, 0);

    if (pid_of_process_A > 0 && pid_of_process_B > 0)  // Parent process
    {
        // Display value of X
        printf("Final value of X: %d \n", *X);

        // Detach from shared memory
        shmdt(X);

        // Destroy shared memory
        shmctl(shmid, IPC_RMID, NULL);
    }

    return 0;
}