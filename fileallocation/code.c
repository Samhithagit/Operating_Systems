#include <stdio.h>


#define MAX_BLOCKS 10
#define MAX_FILES 5


void sequentialAllocation(int files[], int n, int blocks[], int m) { int allocated[MAX_FILES] = {0};
int fileStart[MAX_FILES] = {-1}; for (int i = 0; i < n; i++) {
if (allocated[i] == 0) { fileStart[i] = blocks[i]; allocated[i] = 1;
printf("File %d allocated to block %d\n", i + 1, blocks[i]);
}
}
}


void indexedAllocation(int files[], int n, int blocks[], int m) { int indexed[MAX_FILES] = {-1};
for (int i = 0; i < n; i++) { indexed[i] = blocks[i];
printf("File %d indexed to block %d\n", i + 1, blocks[i]);
}
}
 
void linkedAllocation(int files[], int n, int blocks[], int m) { int nextBlock[MAX_BLOCKS];
for (int i = 0; i < m; i++) { nextBlock[i] = -1;
}
for (int i = 0; i < n; i++) { if (i < m - 1) {
nextBlock[blocks[i]] = blocks[i + 1];
printf("File %d linked to block %d, next block: %d\n", i + 1, blocks[i], nextBlock[blocks[i]]);
} else {
printf("File %d linked to block %d, next block: NULL\n", i + 1, blocks[i]);
}
}
}


int main() { int n, m;
int files[MAX_FILES], blocks[MAX_BLOCKS];


printf("Enter the number of files (max 5): "); scanf("%d", &n);

printf("Enter the number of blocks (max 10): "); scanf("%d", &m);

printf("Enter the block numbers for each file (0 to %d):\n", m - 1); for (int i = 0; i < n; i++) {
printf("File %d: ", i + 1);
scanf("%d", &blocks[i]);
}


printf("\nSequential Allocation:\n");
 
sequentialAllocation(files, n, blocks, m);


printf("\nIndexed Allocation:\n"); indexedAllocation(files, n, blocks, m);

printf("\nLinked Allocation:\n"); linkedAllocation(files, n, blocks, m);

return 0;
}
