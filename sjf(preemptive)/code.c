#include <stdio.h> #include <limits.h>

void findWaitingTime(int n, int at[], int bt[], int wt[]) { int rt[n];
for (int i = 0; i < n; i++) rt[i] = bt[i];

int complete = 0, t = 0, min_index, min_rt; int finish_time;
int shortest = -1; int check = 0;
 
while (complete != n) { min_rt = INT_MAX;
for (int j = 0; j < n; j++) {
if (at[j] <= t && rt[j] > 0 && rt[j] < min_rt) { min_rt = rt[j];
shortest = j; check = 1;
}
}

if (check == 0) { t++;
continue;
}

rt[shortest]--;
min_rt = rt[shortest];
if (rt[shortest] == 0) { complete++; finish_time = t + 1;
wt[shortest] = finish_time - at[shortest] - bt[shortest];

if (wt[shortest] < 0) wt[shortest] = 0;
}
t++;
}
}

void findTurnAroundTime(int n, int at[], int bt[], int wt[], int tat[]) { for (int i = 0; i < n; i++)
tat[i] = bt[i] + wt[i];
}

void findAvgTime(int n, int at[], int bt[]) { int wt[n], tat[n];
float total_wt = 0, total_tat = 0;
findWaitingTime(n, at, bt, wt); findTurnAroundTime(n, at, bt, wt, tat);

printf("\nProcess\tAT\tBT\tWT\tTAT\n"); for (int i = 0; i < n; i++) {
total_wt += wt[i]; total_tat += tat[i];
printf("%d\t%d\t%d\t%d\t%d\n", i + 1, at[i], bt[i], wt[i], tat[i]);
}
printf("\nAverage Waiting Time = %.2f", total_wt / n); printf("\nAverage Turnaround Time = %.2f\n", total_tat / n);
}

int main() { int n;
printf("Enter the number of processes: "); scanf("%d", &n);

int at[n], bt[n];
printf("Enter Arrival Time and Burst Time for each process:\n");
 
for (int i = 0; i < n; i++) { printf("Process %d: ", i + 1); scanf("%d %d", &at[i], &bt[i]);
}
findAvgTime(n, at, bt);

return 0;
}
