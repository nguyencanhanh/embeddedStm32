/*
 * queue.c
 *
 *  Created on: Dec 21, 2023
 *      Author: nguye
 */
#include "queue.h"

void initDynamicQueue(struct DynamicQueue *queue, int capacity) {
    queue->front = -1;
    queue->rear = -1;
    queue->capacity = capacity;
    queue->items = (char **)malloc(capacity * sizeof(char *));

    if (queue->items == NULL) {
        exit(EXIT_FAILURE);
    }
}

int isFullDynamic(struct DynamicQueue *queue) {
    return (queue->rear == queue->capacity - 1);
}

int isEmptyDynamic(struct DynamicQueue *queue) {
    return (queue->front == -1 || queue->front > queue->rear);
}

void enqueueDynamic(struct DynamicQueue *queue, const char *value) {
	if (queue->front == -1) {
		queue->front = 0;
	}
	queue->rear++;
	queue->items[queue->rear] = strdup(value);
}

char* dequeueDynamic(struct DynamicQueue *queue) {
	char *removedValue = queue->items[queue->front];
	queue->front++;
	return removedValue;
}

