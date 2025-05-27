// FCFS CPU Scheduling
#include <stdio.h>

void fcfs_schedule(int proc_id[], int at[], int bt[], int n) {
    int temp, c = 0;
    int ct[n], tat[n], wt[n];
    double avg_tat = 0.0, avg_wt = 0.0, twat = 0.0, twt = 0.0;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (at[i] > at[j]) {
                temp = at[i];
                at[i] = at[j];
                at[j] = temp;

                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;

                temp = proc_id[i];
                proc_id[i] = proc_id[j];
                proc_id[j] = temp;
            }
        }

        if (c >= at[i]) {
            c += bt[i];
        } else {
            c = at[i] + bt[i];
        }
        ct[i] = c;
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        twat += tat[i];
        twt += wt[i];
    }

    avg_tat = twat / n;
    avg_wt = twt / n;

    printf("FCFS scheduling:\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", proc_id[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage turnaround time: %lf ms\n", avg_tat);
    printf("Average waiting time: %lf ms\n", avg_wt);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    int proc_id[n], at[n], bt[n];
    
    for (int i = 0; i < n; i++) {
        proc_id[i] = i + 1;
    }
    
    printf("Enter arrival times:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &at[i]);
    }
    printf("Enter burst times:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &bt[i]);
    }

    fcfs_schedule(proc_id, at, bt, n);

    return 0;
}
