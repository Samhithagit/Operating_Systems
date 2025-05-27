#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_ITEMS 5
#define BUFFER_SIZE 5


int buffer[BUFFER_SIZE]; int in = 0, out = 0;
sem_t mutex; sem_t full; sem_t empty;
int produced_count = 0, consumed_count = 0;


void *producer(void *arg) { sem_wait(&empty); sem_wait(&mutex);

buffer[in] = produced_count + 1;
printf("Producer has produced: Item %d\n", buffer[in]); in = (in + 1) % BUFFER_SIZE;
produced_count++; sem_post(&mutex);
 
sem_post(&full); pthread_exit(NULL);
}


void *consumer(void *arg) { sem_wait(&full); sem_wait(&mutex);

int last_item_index = (in - 1 + BUFFER_SIZE) % BUFFER_SIZE; printf("Consumer has consumed: Item %d\n", buffer[last_item_index]); buffer[last_item_index] = 0;
consumed_count++;


in = (in - 1 + BUFFER_SIZE) % BUFFER_SIZE;


sem_post(&mutex); sem_post(&empty); pthread_exit(NULL);
}


int main() {
pthread_t prod_thread, cons_thread; int choice;

sem_init(&mutex, 0, 1);
sem_init(&full, 0, 0);
sem_init(&empty, 0, MAX_ITEMS);
while (1) {
printf("Enter 1.Producer 2.Consumer 3.exit\n"); printf("Enter choice: ");
scanf("%d", &choice);
 
switch (choice) { case 1:
if (produced_count < MAX_ITEMS) { pthread_create(&prod_thread, NULL, producer, NULL); pthread_join(prod_thread, NULL);
} else {
printf("Buffer is full. Cannot produce more items.\n");
}
break; case 2:
if (consumed_count < produced_count) { pthread_create(&cons_thread, NULL, consumer, NULL); pthread_join(cons_thread, NULL);
} else {
printf("Buffer is empty. Cannot consume more items.\n");
}
break; case 3:
sem_destroy(&mutex); sem_destroy(&full); sem_destroy(&empty); return 0;
default:
printf("Invalid choice.\n");
}
}


return 0;
}
