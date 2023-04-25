#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
struct process{
    int pid,at,bt,ct,wt,tat,start_time;
};
int main()
{
    int n;
    printf("Enter total no. of processes: ");
    scanf("%d", &n);
    struct process arr[n];
    float bt_remaining[100];

    for (int i=0; i<n; i++){
        struct process *ptr = arr+i;
        ptr->pid = i+1;
        printf("Process %d\nEnter arrival time: ", ptr->pid);
        scanf("%d", &ptr->at);
        printf("Enter burst time: ");
        scanf("%d", &ptr->bt);
        bt_remaining[i]=ptr->bt;
    }

    int completed = 0, current_time = 0;
    bool is_completed[100] = {false};
    float avgTAT=0, avgWT=0;
    while (completed != n)
    {
        int min_index = -1; //index of process with minimum burst time
        int minimum = INT_MAX; //minimum burst time
        
        for (int i=0; i<n; i++){
            if (arr[i].at <= current_time && is_completed[i] == false)
            {
                if (bt_remaining[i] < minimum){
                    min_index = i;
                    minimum = bt_remaining[i];
                }
                if (bt_remaining[i] == minimum){
                    if (arr[i].at < arr[min_index].at){
                        min_index = i;
                        minimum = bt_remaining[i];
                    }
                }
            }
        }

        if (min_index==-1)
            current_time++;
        else{
            // if (bt_remaining[min_index] == arr[min_index].bt)
            //     arr[min_index].start_time = current_time; //if process has not started current time is the start time
            bt_remaining[min_index] -= 1;
            current_time++;
             //process burst time completed
            if (bt_remaining[min_index] == 0){ 
                arr[min_index].ct = current_time;
                arr[min_index].tat = arr[min_index].ct - arr[min_index].at;
                arr[min_index].wt = arr[min_index].tat - arr[min_index].bt;
                avgTAT+=arr[min_index].tat;
                avgWT+=arr[min_index].wt;
                completed++;
                is_completed[min_index]=true;
            }
        }
    }

    

    printf("\nP#\tAT\tCPU Burst Time\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t\t%d\t%d\t%d\n", arr[i].pid, arr[i].at, arr[i].bt, arr[i].ct, arr[i].tat, arr[i].wt);
    printf("\n");
    printf("\nAverage Turn Around time= %f ",avgTAT/n);
    printf("\nAverage Waiting Time= %f ",avgWT/n);
    return 0;
}