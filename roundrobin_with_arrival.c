#include <stdio.h>

struct process {
    int pid, at, bt, ct, wt, tat, remaining_bt;
};

int main() {
    int n;
    int quantum;
    printf("Enter total number of processes: ");
    scanf("%d", &n);
    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    struct process arr[n];
    for (int i = 0; i < n; i++) {
        struct process *ptr = &arr[i];
        ptr->pid = i + 1;
        printf("Process %d\nEnter arrival time: ", ptr->pid);
        scanf("%d", &ptr->at);
        printf("Enter burst time: ");
        scanf("%d", &ptr->bt);
        ptr->remaining_bt = ptr->bt;
    }

    int time = 0;
    int completed = 0;
    while (completed < n) {
        int flag = 0;  // Added flag to break out of loop
        for (int i = 0; i < n; i++) {
            struct process *ptr = &arr[i];
            if (ptr->at <= time && ptr->remaining_bt > 0) {
                int min_time = (ptr->remaining_bt < quantum) ? ptr->remaining_bt : quantum;
                time += min_time;
                ptr->remaining_bt -= min_time;

                if (ptr->remaining_bt == 0) {
                    completed++;
                    ptr->ct = time;
                    ptr->tat = ptr->ct - ptr->at;
                    ptr->wt = ptr->tat - ptr->bt;
                }

                flag = 1;  // Set flag to indicate a process was executed
            }
        }
        if (flag == 0) {
            time++;  // Increment time if no process was executed
        }
    }

    float avgWT = 0, avgTAT = 0;
    printf("\nP#\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        struct process *ptr = &arr[i];
        avgTAT += ptr->tat;
        avgWT += ptr->wt;
        printf("%d\t%d\t%d\t%d\t%d\n", ptr->pid, ptr->bt, ptr->ct, ptr->tat, ptr->wt);
    }

    printf("Average Turnaround Time (TAT): %.2f\n", avgTAT / n);
    printf("Average Waiting Time (WT): %.2f\n", avgWT / n);

    return 0;
}
