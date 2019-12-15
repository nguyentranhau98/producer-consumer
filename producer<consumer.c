#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>


#define size 10			//size of bounder buffer
int empty = size; 	//value of semaphore empty
int full = 0;				//value of semaphore full
int mutex = 1;			//value of semaphore mutex
int itemCount = 0;	//items produced

//queue implementation
int intArray[size];
int front = 0;
int rear = -1;

void show() {
	for (int i = 0; i < size; i++) {
		printf("-%d-", intArray[i]);
	}
	printf("\n");
}

int peek() {
	return intArray[front];
}

bool isEmpty() {
	return itemCount == 0;
}

bool isFull() {
	return itemCount == size;
}

int sizeofArray() {
	return itemCount;
}

void insert(int data) {
	if (!isFull()) {
		if (rear == size - 1) {
			rear = -1;
		}
		intArray[++rear] = data;
		itemCount++;
	}
}

int removeData() {
	int data = intArray[front++];
	intArray[front - 1] = 0;
	if (front == size) {
		front = 0;
	}
	itemCount--;
	return data;
}
////////////////////////////////////////////////

//up and down operation implementation
void down(int *a, int s) {
	while (*a <= 0)
		;	// do nothing
	*a = *a - 1;
}

void up(int *a, int n) {
	*a = *a + 1;
	if (*a > 1 && n == 1)
		*a = 1;
}
////////////////////////////////////////////////

//producer and consumer implementation
void *consumer(void *arg) {
	do {
		sleep(2);
		// printf("\nConsumer %s begin\n", (char *) arg);
		down(&full, 1);
		down(&mutex, 2);
		printf("\nTruoc khi tieu thu:\n");
		show();
		int r = removeData();
		printf("\nconsumer %s tieu thu:%d \n", (char *)arg, r);
		show();
		up(&mutex, 1);
		up(&empty, 2);
	} while (1);
	return NULL;
}

void *producer(void *arg) {
	do {
		if (full <= size) {
			sleep(2);
			// printf("\nProducer %s begin\n", (char *) arg);
			int r = rand() % 100 + 1; //generate data (a random number from 1 to 100)
			down(&empty, 3);					
			down(&mutex, 4);					
			printf("\nTruoc khi San xuat:\n");
			show();
			insert(r);
			printf("\nProducer %s tao ra:%d \n", (char *)arg, r);
			show();
			up(&mutex, 1);
			up(&full, 2);
		}
	} while (1);
	return NULL;
}
////////////////////////////////////////////////

int main() {
	//create producer threads and consumer threads
	pthread_t producerThread;
	pthread_create(&producerThread, NULL, producer, "1");
	pthread_t producerThread2;
	pthread_create(&producerThread2, NULL, producer, "2");

	pthread_t consumerThread;
	pthread_create(&consumerThread, NULL, consumer, "1");
	pthread_t consumerThread2;
	pthread_create(&consumerThread2, NULL, consumer, "2");
	pthread_t consumerThread3;
	pthread_create(&consumerThread3, NULL, consumer, "3");
	pthread_t consumerThread4;
	pthread_create(&consumerThread4, NULL, consumer, "4");
	pthread_t consumerThread5;
	pthread_create(&consumerThread5, NULL, consumer, "5");

	while (1)
		;	//infinite loop

}
