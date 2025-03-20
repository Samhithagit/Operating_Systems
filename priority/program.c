#include <stdio.h>
void calculate_times(int n, int burst_time[], int priority[], int arrival_time[], int completion_time[], int waiting_time[], int turnaround_time[]) {
    int total_waiting_time = 0, total_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        turnaround_time[i] = completion_time[i] - arrival_time[i];
        waiting_time[i] = turnaround_time[i] - burst_time[i];
        total_waiting_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i];
    }
    printf("\nProcess\tBurst Time\tArrival Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, burst_time[i], arrival_time[i], priority[i], waiting_time[i], turnaround_time[i]);
    }
    printf("\nAverage Waiting Time: %.2f", (float)total_waiting_time / n);
    printf("\nAverage Turnaround Time: %.2f", (float)total_turnaround_time / n);
}
void priority_scheduling(int n, int burst_time[], int priority[], int arrival_time[]) {
    int remaining_time[n];
    int completion_time[n];
    int waiting_time[n];
    int turnaround_time[n];
    int completed = 0, current_time = 0;
    int min_priority;
    for (int i = 0; i < n; i++) {
        remaining_time[i] = burst_time[i];
    }
    while (completed < n) {
        min_priority = -1;
        for (int i = 0; i < n; i++) {
            if (remaining_time[i] > 0 && arrival_time[i] <= current_time && (min_priority == -1 || priority[i] < priority[min_priority])) {
                min_priority = i;
            }
        }
        if (min_priority != -1) {
            remaining_time[min_priority]--;
            current_time++;
            if (remaining_time[min_priority] == 0) {
                completion_time[min_priority] = current_time;
                completed++;
            }
        } else {
            current_time++;
        }
    }
    calculate_times(n, burst_time, priority, arrival_time, completion_time, waiting_time, turnaround_time);
}
int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    int burst_time[n], priority[n], arrival_time[n];
    for (int i = 0; i < n; i++) {
        printf("\nEnter Burst Time, Priority, and Arrival Time for Process %d:\n", i + 1);
        printf("Burst Time: ");
        scanf("%d", &burst_time[i]);
        printf("Priority: ");
        scanf("%d", &priority[i]);
        printf("Arrival Time: ");
        scanf("%d", &arrival_time[i]);
    }
    priority_scheduling(n, burst_time, priority, arrival_time);
    return 0;
}
