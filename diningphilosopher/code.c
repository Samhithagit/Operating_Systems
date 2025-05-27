#include <stdio.h> #include <stdlib.h>
 
#include <pthread.h> #include <semaphore.h> #include <unistd.h>

#define NUM_PHILOSOPHERS 5
#define THINKING 0
#define HUNGRY 1
#define EATING 2


int state[NUM_PHILOSOPHERS];
int phil_ids[NUM_PHILOSOPHERS];


sem_t mutex;
sem_t S[NUM_PHILOSOPHERS];


void test(int i) {
if (state[i] == HUNGRY &&
state[(i + 4) % NUM_PHILOSOPHERS] != EATING && state[(i + 1) % NUM_PHILOSOPHERS] != EATING) {

state[i] = EATING; sleep(1);
printf("Philosopher %d takes forks %d and %d and starts eating\n", i + 1, (i + 4) % NUM_PHILOSOPHERS + 1, i + 1);
sem_post(&S[i]);
}
}


void take_fork(int i) { sem_wait(&mutex); state[i] = HUNGRY;
printf("Philosopher %d is hungry\n", i + 1); test(i);
 
sem_post(&mutex); sem_wait(&S[i]); sleep(1);
}


void put_fork(int i) { sem_wait(&mutex); state[i] = THINKING;
printf("Philosopher %d puts down forks %d and %d and starts thinking\n", i + 1, (i + 4) % NUM_PHILOSOPHERS + 1, i + 1);
test((i + 4) % NUM_PHILOSOPHERS); test((i + 1) % NUM_PHILOSOPHERS);
sem_post(&mutex);
}


void* philosopher(void* num) { int i = *(int*)num;

while (1) {
printf("Philosopher %d is thinking\n", i + 1); sleep(1);
take_fork(i); sleep(2); put_fork(i);
}


return NULL;
}


int main() { int i;
pthread_t thread_id[NUM_PHILOSOPHERS]; sem_init(&mutex, 0, 1);
 
for (i = 0; i < NUM_PHILOSOPHERS; i++) {
sem_init(&S[i], 0, 0); phil_ids[i] = i;
}


for (i = 0; i < NUM_PHILOSOPHERS; i++) {
pthread_create(&thread_id[i], NULL, philosopher, &phil_ids[i]); printf("Philosopher %d is seated at the table\n", i + 1);
}


for (i = 0; i < NUM_PHILOSOPHERS; i++) {
pthread_join(thread_id[i], NULL);
}


return 0;
}
