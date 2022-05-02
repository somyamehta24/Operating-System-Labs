//Somya Mehta
// 190001058
#include <stdio.h>
#include <stdlib.h>



typedef struct process {
    int pid;
    int arrive_tim;
    int is_completed;
    int burst_tim;
    int wait_tim;
    int turnaround_tim;
} process;


//Comparator function
int sortByArrival(const void *a, const void *b) {
    int A = ((process*)a)->arrive_tim;
    int B = ((process*)b)->arrive_tim;
    return A - B;
}

int TOTAL_PROCESSES =5;

process proc[5];
void input()
{
    for (int i = 0; i < TOTAL_PROCESSES; i++) {
        printf("Process %d:\n", i + 1);
        printf("Enter pid of process");
        scanf("%d", &(proc[i].pid));
        printf("Enter arrival time of process");
        scanf("%d", &(proc[i].arrive_tim));
        printf("Enter burst time of process");
        scanf("%d", &(proc[i].burst_tim));
    }
}
void fcfs()
{
    // sort according to arrival time
    qsort(proc, TOTAL_PROCESSES, sizeof(process), sortByArrival);
}
void scheduler()
{

    int curr_time = proc[0].arrive_tim;  // initialize current time with arrival of first processes
    for (int i = 0; i < TOTAL_PROCESSES; i++) {
        proc[i].wait_tim = curr_time - proc[i].arrive_tim;
        if (proc[i].wait_tim < 0) proc[i].wait_tim = 0,curr_time=proc[i].arrive_tim;
        proc[i].turnaround_tim = proc[i].wait_tim + proc[i].burst_tim;
        curr_time += proc[i].burst_tim;
    }
}
void PrintGanttChart()
{
    // show gantt chart with average waiting and turnaround times
    printf("\nGantt Chart\n\t");
    for (int i = 0; i < TOTAL_PROCESSES; i++) {
        printf("(PID:%d)\t\t", proc[i].pid);
    }
    printf("\n");
    printf("--%d--\t\t", proc[0].arrive_tim);
    for (int i = 1; i <= TOTAL_PROCESSES; i++) {
        printf("--%d--\t\t", proc[i - 1].turnaround_tim + proc[i - 1].arrive_tim);
    }
    printf("\n");
}
int main(int argc, char const *argv[]) {
    printf("\t\tFirst Come First Serve Algo\n");


    input();    

    
    scheduler();

    PrintGanttChart();

    float total_waiting = 0, total_turnaround = 0;
    for (int i = 0; i < TOTAL_PROCESSES; i++) {
        total_waiting += proc[i].wait_tim;
        total_turnaround += proc[i].turnaround_tim;
    }
    printf("Average Waiting Time: %f\nAverage Turnaround Time: %f", total_waiting / TOTAL_PROCESSES, total_turnaround / TOTAL_PROCESSES);
    
    printf("\nPID\tArrival\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < TOTAL_PROCESSES; i++) {
        printf("%d\t%d\t%d\t%d\t%d\n", proc[i].pid, proc[i].arrive_tim, proc[i].burst_tim, proc[i].wait_tim, proc[i].turnaround_tim);
    }
    return 0;
}
