//Somya Mehta
// 190001058
#include <stdio.h>
#include <stdlib.h>

int min(int a,int b)
{
    if(a<b)
    return a;
    return b;
}

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

int TOTAL_PROCESSES =4,Time_Quantum,Context_Switch_Time,TOTAL_Context_Switch=0;

process proc[5],temp[5];
void input()
{
    printf("Enter Time Quanta= ");
    scanf("%d",&Time_Quantum);
    printf("Enter Context Switch time= ");
    scanf("%d",&Context_Switch_Time);
    for (int i = 0; i < TOTAL_PROCESSES; i++) {
        printf("Enter pid of process: ");
        scanf("%d", &(proc[i].pid));
        printf("Enter arrival time of process: ");
        scanf("%d", &(proc[i].arrive_tim));
        printf("Enter burst time of process: ");
        scanf("%d", &(proc[i].burst_tim));
    }
}
void rr()
{
    // sort according to arrival time
    qsort(proc, TOTAL_PROCESSES, sizeof(process), sortByArrival);
}
void scheduler()
{
    printf("\n\t\t\t-----------------Gantt Chart----------------\n\n\n\n\t");
    for(int i=0;i<TOTAL_PROCESSES;i++)
    {
        temp[i]=proc[i];
    }
    int curr_time = proc[0].arrive_tim;  // initialize current time with arrival of first processes
    int j=0;
    while(1)
    {
        int k=0,p=0,time=1000000000;

        // Counting the already completed processes
        for(int i=0;i<TOTAL_PROCESSES;i++)
        {

            if(proc[i].burst_tim==0)
            {
                k++;
                // continue;
            }
        }

        //executing each incomplete process for the time quanta period 
        for (int i = 0; i < TOTAL_PROCESSES; i++)
        {
            if(proc[i].burst_tim==0)
            {
                continue;
            }
            // considering the corner cases for the processes whose arrival time is very late
            if(proc[i].arrive_tim>curr_time)
            {
                p++;
                time=min(time,proc[i].arrive_tim);
                continue;
            }
            printf("(PID:%d)\t\t", proc[i].pid);
            if(proc[i].burst_tim>=Time_Quantum)
            {
                curr_time+=Time_Quantum;
                proc[i].burst_tim-=Time_Quantum;
            }
            else
            {
                curr_time+=proc[i].burst_tim;
                proc[i].burst_tim=0;
            }
            if(proc[i].burst_tim==0)
            proc[i].turnaround_tim=curr_time-proc[i].arrive_tim;
            if(proc[i].burst_tim==0&&k==TOTAL_PROCESSES-1)
            {}
            else 
            {
                curr_time+=Context_Switch_Time;
                TOTAL_Context_Switch++;
            }
        }
        if(k==TOTAL_PROCESSES)break;// if all process complete
        //Corner case where arrival time of the next process is greater than
        // the current time and all the other processes are complete
        if(p+k==TOTAL_PROCESSES) 
        {
            curr_time=time;
        }
    }
        printf("\n");

}
void PrintGanttChart()
{
    // Running the algo again to display the Gantt chart properly
    int curr_time1=temp[0].arrive_tim;
    for(int i=0;i<TOTAL_PROCESSES;i++)
    {
        proc[i].burst_tim=temp[i].burst_tim;
    }
    int j=1;
    while(1)
    {
        int k=0,p=0,time=1000000000;

        for(int i=0;i<TOTAL_PROCESSES;i++)
        {

            if(temp[i].burst_tim==0)
            {
                k++;
                // continue;
            }
        }

        for (int i = 0; i < TOTAL_PROCESSES; i++)
        {
            if(temp[i].burst_tim==0)
            {
                continue;
            }
            if(temp[i].arrive_tim>curr_time1)
            {
                p++;
                time=min(time,temp[i].arrive_tim);
                continue;
            }
            if(j==1)
            printf("--%d--\t\t", curr_time1),j=0;
            if(temp[i].burst_tim>=Time_Quantum)
            {
                curr_time1+=Time_Quantum;
                temp[i].burst_tim-=Time_Quantum;
            }
            else
            {
                curr_time1+=temp[i].burst_tim;
                temp[i].burst_tim=0;
            }
            if(temp[i].burst_tim==0&&k==TOTAL_PROCESSES-1)
            {}
            else
            {
                curr_time1+=Context_Switch_Time;
            }
            
            printf("--%d--\t\t",curr_time1);
        }
        if(k==TOTAL_PROCESSES)break;
        if(p+k==TOTAL_PROCESSES)
        {
            curr_time1=time;
            j=1;
        }
        else
        j=0;
    }
    for(int i=0;i<TOTAL_PROCESSES;i++)
    {
        proc[i].wait_tim=proc[i].turnaround_tim-proc[i].burst_tim;
    }
    printf("\n");
    printf("\nTotal Context Switches= %d \n",TOTAL_Context_Switch);
    float ans=curr_time1-TOTAL_Context_Switch*Context_Switch_Time;
    printf("\nTotal CPU Utilization= %f %%\n",(ans/curr_time1)*100.00);
}
int main(int argc, char const *argv[]) {

    printf("\t\t Round Robin Algo\n");


    input();    //user input

    rr();//Sorting the queue according to the arrival time
        
    scheduler(); //Round Robin Scheduling ALgo implented here

    PrintGanttChart(); // printing Gantt chart

    //Calculation of average waiting,turnaround time
    float total_waiting = 0, total_turnaround = 0;
    for (int i = 0; i < TOTAL_PROCESSES; i++) {
        total_waiting += proc[i].wait_tim;
        total_turnaround += proc[i].turnaround_tim;
    }

    //Display of average waiting,turnaround time

    printf("Average Waiting Time: %f\nAverage Turnaround Time: %f", total_waiting / TOTAL_PROCESSES, total_turnaround / TOTAL_PROCESSES);
    
    printf("\nPID\tArrival\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < TOTAL_PROCESSES; i++) {
        printf("%d\t%d\t%d\t%d\t%d\n", proc[i].pid, proc[i].arrive_tim, proc[i].burst_tim, proc[i].wait_tim, proc[i].turnaround_tim);
    }
    return 0;
}