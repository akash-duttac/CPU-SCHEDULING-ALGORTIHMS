#include <stdio.h>
#include <stdlib.h>

#define QUANTUM 2

struct process{
    int pid, bt, wt, ct, rt, tat; // here rt is remaining time
};

int main()
{
    int n;
    printf("Enter no. of processes: ");
    scanf("%d", &n);

    struct process arr[n];

    printf("Enter burst time for each process\n");
    for (int i = 0; i < n; i++){
        struct process *ptr = arr + i;
        ptr->pid = i + 1;
        printf("Process %d: ", ptr->pid);
        scanf("%d", &ptr->bt);
        ptr->rt = ptr->bt;
    }

    int timeElapsed = 0;
    while(1)
    {
        int complete=1;
        for (int i=0; i<n; i++){
            struct process *ptr = arr + i;
            if (ptr->rt > 0){
                complete=0;
                if (ptr->rt <= QUANTUM){
                    timeElapsed += ptr->rt;
                    ptr->rt = 0;
                    ptr->ct = timeElapsed;
                    ptr->tat = ptr->ct;
                }
                else{
                    timeElapsed += QUANTUM;
                    ptr->rt -= QUANTUM;
                }
            }   
        }
        if (complete == 1)
            break;
    }

    float totalWT=0, totalTAT=0;
    printf("\nP#\tBT\tCT\tWT\tTAT\n");
    for (int i=0; i<n; i++){
        struct process *ptr = arr+i;
        ptr->wt = ptr->tat - ptr->bt;
        printf("%d\t%d\t%d\t%d\t%d\n",ptr->pid,ptr->bt,ptr->ct,ptr->wt,ptr->tat);
        totalWT += ptr->wt;
        totalTAT += ptr->tat;
    }

    totalWT /= n;
    totalTAT /= n;

    printf("\nAvg. TAT = %.2f\nAvg. WT = %.2f", totalTAT, totalWT);
    return 0;
}