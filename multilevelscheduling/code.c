#include <stdio.h>
int main() {
int bt[20], wt[20], tat[20], ct[20], queue[20]; int n;
float wtavg = 0, tatavg = 0; int sys_bt[20], user_bt[20];
int sys_count = 0, user_count = 0;


printf("Enter the number of processes: "); scanf("%d", &n);

for (int i = 0; i < n; i++) {
printf("Enter Burst Time for Process %d: ", i + 1); scanf("%d", &bt[i]);
printf("Enter Queue Number (1 = System, 2 = User) for Process %d: ", i + 1); scanf("%d", &queue[i]);

if (queue[i] == 1) { sys_bt[sys_count++] = bt[i];
} else if (queue[i] == 2) { user_bt[user_count++] = bt[i];
}
}


5
 
int total_count = 0; int current_time = 0;

for (int i = 0; i < sys_count; i++) { if (total_count == 0) {
wt[total_count] = 0;
} else {
wt[total_count] = current_time;
}


tat[total_count] = wt[total_count] + sys_bt[i]; ct[total_count] = current_time + sys_bt[i];

current_time = ct[total_count];


wtavg += wt[total_count]; tatavg += tat[total_count]; total_count++;
}


for (int i = 0; i < user_count; i++) { if (total_count == 0) {
wt[total_count] = 0;
} else {
wt[total_count] = current_time;
}


tat[total_count] = wt[total_count] + user_bt[i]; ct[total_count] = current_time + user_bt[i];

current_time = ct[total_count]; wtavg += wt[total_count];
 
tatavg += tat[total_count]; total_count++;
}


printf("\nPROCESS\tBURST TIME\tQUEUE\tCOMPLETION TIME\tWAITING TIME\tTURNAROUND TIME\n");
int sys_index = 0, user_index = 0; for (int i = 0; i < total_count; i++) {
if (sys_index < sys_count) {
printf("%d\t%d\t\tSystem\t%d\t\t%d\t\t%d\n", i + 1, sys_bt[sys_index], ct[i], wt[i], tat[i]); sys_index++;
} else if (user_index < user_count) {
printf("%d\t%d\t\tUser\t%d\t\t%d\t\t%d\n", i + 1, user_bt[user_index], ct[i], wt[i], tat[i]); user_index++;
}
}


printf("\nAverage Waiting Time: %.2f", wtavg / total_count); printf("\nAverage Turnaround Time: %.2f\n", tatavg / total_count);

return 0;
}
