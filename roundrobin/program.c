#include <stdio.h>

int main() {
    int n, time_quantum, total_waiting_time = 0, total_turnaround_time = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    printf("Enter time quantum: ");
    scanf("%d", &time_quantum);
    
    int burst_time[n], remaining_time[n], waiting_time[n], turnaround_time[n], completion_time[n], arrival_time[n];
    
    for (int i = 0; i < n; i++) {
        printf("Enter burst time and arrival time for process %d: ", i + 1);
        scanf("%d %d", &burst_time[i], &arrival_time[i]);
        remaining_time[i] = burst_time[i];
    }
    
    int current_time = 0, completed = 0;
    
    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (remaining_time[i] > 0 && arrival_time[i] <= current_time) {
                if (remaining_time[i] > time_quantum) {
                    current_time += time_quantum;
                    remaining_time[i] -= time_quantum;
                } else {
                    current_time += remaining_time[i];
                    completion_time[i] = current_time;
                    remaining_time[i] = 0;
                    completed++;
                }
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        turnaround_time[i] = completion_time[i] - arrival_time[i];
        waiting_time[i] = turnaround_time[i] - burst_time[i];
        total_waiting_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i];
    }
    
    printf("\nProcess\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, burst_time[i], arrival_time[i], waiting_time[i], turnaround_time[i]);
    }
    
    printf("\nAverage Waiting Time: %.2f", (float)total_waiting_time / n);
    printf("\nAverage Turnaround Time: %.2f", (float)total_turnaround_time / n);
    
    return 0;
}
