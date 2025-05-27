#include <stdio.h>
#include <limits.h>

void fifo(int pages[], int n, int capacity){
int frames[capacity], index = 0, faults = 0;
for (int i = 0; i < capacity; i++) frames[i] = -1;


printf("\nFIFO Page Replacement\n"); for (int i = 0; i < n; i++) {
int found = 0;
for (int j = 0; j < capacity; j++) { if (frames[j] == pages[i]) {
found = 1; break;
}
}
if (!found) {
frames[index] = pages[i]; index = (index + 1) % capacity; faults++;
}


printf("Frames: ");
for (int j = 0; j < capacity; j++) {
 
if (frames[j] == -1) printf(" - ");
else
printf(" %d ", frames[j]);
}
printf("\n");
}
printf("Total Page Faults: %d\n", faults);
}


void lru(int pages[], int n, int capacity) {
int frames[capacity], recent[capacity], faults = 0;


for (int i = 0; i < capacity; i++) frames[i] = -1;


printf("\nLRU Page Replacement\n"); for (int i = 0; i < n; i++) {
int found = 0;
for (int j = 0; j < capacity; j++) { if (frames[j] == pages[i]) {
recent[j] = i; found = 1; break;
}
}


if (!found) {
int lru_index = 0;
for (int j = 1; j < capacity; j++) {
if (frames[j] == -1 || recent[j] < recent[lru_index]) lru_index = j;
}
 
frames[lru_index] = pages[i]; recent[lru_index] = i; faults++;
}


printf("Frames: ");
for (int j = 0; j < capacity; j++) { if (frames[j] == -1)
printf(" - "); else
printf(" %d ", frames[j]);
}
printf("\n");
}
printf("Total Page Faults: %d\n", faults);
}


void optimal(int pages[], int n, int capacity) { int frames[capacity], faults = 0;

for (int i = 0; i < capacity; i++) frames[i] = -1;


printf("\nOptimal Page Replacement\n"); for (int i = 0; i < n; i++) {
int found = 0;
for (int j = 0; j < capacity; j++) { if (frames[j] == pages[i]) {
found = 1; break;
}
}
 
if (!found) {
int opt_index = -1, farthest = i; for (int j = 0; j < capacity; j++) {
if (frames[j] == -1) { opt_index = j; break;
}
int next_use = INT_MAX; for (int k = i + 1; k < n; k++) {
if (frames[j] == pages[k]) { next_use = k;
break;
}
}
if (next_use > farthest) { farthest = next_use; opt_index = j;
}
}
frames[opt_index] = pages[i]; faults++;
}


printf("Frames: ");
for (int j = 0; j < capacity; j++) { if (frames[j] == -1)
printf(" - "); else
printf(" %d ", frames[j]);
}
printf("\n");
}
 
printf("Total Page Faults: %d\n", faults);
}


int main() {
int n, capacity;
printf("Enter number of pages: "); scanf("%d", &n);
int pages[n];
printf("Enter the page reference string: ");
for (int i = 0; i < n; i++) scanf("%d", &pages[i]); printf("Enter number of frames: "); scanf("%d", &capacity);

fifo(pages, n, capacity); lru(pages, n, capacity); optimal(pages, n, capacity);

return 0;
}
