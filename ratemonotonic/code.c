#include <stdio.h> #include <stdlib.h> #include <stdbool.h>

#define MAX_TASKS 10


int gcd(int a, int b) {
return (b == 0) ? a : gcd(b, a % b);
}


int find_lcm(int periods[], int n) { int lcm = periods[0];
for (int i = 1; i < n; i++) {
lcm = (lcm * periods[i]) / gcd(lcm, periods[i]);
}
return lcm;
}


void rate_monotonic(int execution_times[], int periods[], int n) {
int time_remaining[MAX_TASKS], next_start_time[MAX_TASKS]; for (int i = 0; i < n; i++) {
time_remaining[i] = 0;
next_start_time[i] = 0;
}


int simulation_time = find_lcm(periods, n);
 
printf("\nRate-Monotonic Scheduling (Simulating till time = %d):\n", simulation_time);


for (int time = 0; time < simulation_time; time++) { int chosen_task = -1;

for (int i = 0; i < n; i++) {
if (time == next_start_time[i]) { time_remaining[i] = execution_times[i]; next_start_time[i] += periods[i];
}
}


for (int i = 0; i < n; i++) {
if (time_remaining[i] > 0) {
if (chosen_task == -1 || periods[i] < periods[chosen_task]) { chosen_task = i;
}
}
}


if (chosen_task != -1) {
printf("Time %d: Task %d\n", time, chosen_task + 1); time_remaining[chosen_task]--;
} else {
printf("Time %d: Idle\n", time);
}
}
}


int main() { int n;
printf("Enter the number of tasks: "); scanf("%d", &n);
 
int execution_times[MAX_TASKS], periods[MAX_TASKS]; for (int i = 0; i < n; i++) {
printf("Enter execution time and period for Task %d: ", i + 1); scanf("%d %d", &execution_times[i], &periods[i]);
}


rate_monotonic(execution_times, periods, n); return 0;
}

