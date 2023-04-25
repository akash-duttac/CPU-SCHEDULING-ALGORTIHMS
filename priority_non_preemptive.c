#include <stdio.h>
#include <stdlib.h>
struct process{
    int pid,at,bt,priority,ct,wt,tat;
};
int main()
{
    int n;
    printf("Enter total no. of processes: ");
    scanf("%d", &n);
    struct process arr[n];
    for (int i=0; i<n; i++){
        struct process *ptr = arr+i;
        ptr->pid = i+1;
        printf("Process %d\nEnter arrival time: ", ptr->pid);
        scanf("%d", &ptr->at);
        printf("Enter burst time: ");
        scanf("%d", &ptr->bt);
        printf("Enter priority: ");
        scanf("%d", &ptr->priority);
    }
    for (int i=0; i<n; i++)
        for (int j=i+1; j<n; j++)
            if (arr[i].at > arr[j].at && arr[i].priority < arr[j].priority){
                struct process temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp; 
            }
    int current_time = 0;
    float avgWT=0, avgTAT=0;
    for (int i=0; i<n; i++){
        struct process *ptr = arr+i;
        if (ptr->at > current_time && current_time==0)
            current_time += ptr->at;
        else if (ptr->at >current_time)
            current_time += current_time-ptr->at;
        current_time += ptr->bt;
        ptr->ct = current_time;
        ptr->tat = ptr->ct - ptr->at;
        ptr->wt = ptr->tat - ptr->bt;
        avgTAT+=ptr->tat;
        avgWT+=ptr->wt;
    }

    printf("\nP#\tPriority\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i=0; i<n; i++){
        struct process *ptr = arr+i;
        printf("%d\t%d\t\t%d\t%d\t%d\t%d\t%d\n", ptr->pid, ptr->priority, ptr->at, ptr->bt, ptr->ct, ptr->tat, ptr->wt);
    }
    printf("\nAverage Waiting Time = %.2f", avgWT/n);
    printf("\nAverage Turnaround Time = %.2f", avgTAT/n);
    return 0;
}