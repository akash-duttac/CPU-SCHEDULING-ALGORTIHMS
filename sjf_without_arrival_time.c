#include <stdio.h>
#include <stdlib.h>
struct process{
    int pid, bt, ct, tat, wt;
};
int main()
{
    int n;
    printf("Enter total no. of processes: ");
    scanf("%d", &n);
    struct process arr[n];
    printf("Enter burst time of each process\n");
    for (int i=0; i<n; i++){
        struct process *ptr = arr + i;
        ptr->pid = i+1;
        printf("Process %d: ", ptr->pid);
        scanf("%d", &ptr->bt);
    }
    //sorting the processes by the burst times
    for (int i=0; i<n; i++){
        for (int j=i+1; j<n; j++){
            if (arr[i].bt > arr[j].bt){
                struct process temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    //shortest job first algo
    int current_time = 0;
    for (int i=0; i<n; i++){
        struct process *ptr = arr+i;
        current_time += ptr->bt;
        ptr->ct = current_time;
    }
    for (int i=0; i<n; i++){
        struct process *ptr = arr + i;
        ptr->tat = ptr->ct;
        ptr->wt = ptr->tat - ptr->bt;
    }
    printf("\nP#\tBT\tCT\tTAT\tWT\n");
    for (int i=0; i<n; i++){
        struct process *ptr = arr+i;
        printf("%d\t%d\t%d\t%d\t%d\n", ptr->pid, ptr->bt, ptr->ct, ptr->tat, ptr->wt);
    }
    return 0;
}