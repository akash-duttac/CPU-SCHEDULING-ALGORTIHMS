#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
struct process{
    int pid, at, bt, priority, ct, wt, tat;
};
int main()
{
    int n;
    printf("Enter total no. of processes: ");
    scanf("%d", &n);
    struct process arr[n];
    int bt_remaining[n];

    for (int i = 0; i < n; i++)
    {
        struct process *ptr = arr + i;
        ptr->pid = i + 1;
        printf("Process %d\nEnter Arrival Time: ", ptr->pid);
        scanf("%d", &ptr->at);
        printf("Enter Burst Time: ");
        scanf("%d", &ptr->bt);
        bt_remaining[i] = ptr->bt;
        printf("Enter priority: ");
        scanf("%d", &ptr->priority);
    }

    int completed=0, current_time=0;
    bool is_completed[100]={false};

    while (completed != n)
    {
        int max_index = -1;
        int maximum = 999999;
        
        for (int i=0; i<n; i++){
            if (arr[i].at <= current_time && is_completed[i]==false){
                if (arr[i].priority < maximum){
                    max_index = i;
                    maximum = arr[i].priority;
                } 
                if (arr[i].priority == maximum){
                    if (arr[i].at < arr[max_index].at){
                        max_index = i;
                        maximum = arr[i].priority;
                    }
                }
            }
        }
        if (max_index==-1)
        current_time++;
        else{
            bt_remaining[max_index]-=1;
            current_time++;
            if (bt_remaining[max_index]==0){
                arr[max_index].ct = current_time;
                arr[max_index].tat = arr[max_index].ct - arr[max_index].at;
                arr[max_index].wt = arr[max_index].tat - arr[max_index].bt;
                completed++;
                is_completed[max_index]=true;
            }
        }
    }

     printf("\nP#\tPri\tAT\tCPU Burst Time\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n", arr[i].pid,arr[i].priority, arr[i].at, arr[i].bt, arr[i].ct, arr[i].tat, arr[i].wt);
    printf("\n");
    return 0;
}