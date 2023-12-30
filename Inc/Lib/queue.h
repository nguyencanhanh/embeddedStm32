/*
 * queue.h
 *
 *  Created on: Dec 21, 2023
 *      Author: nguye
 */

#ifndef INC_QUEUE_H_
#define INC_QUEUE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct DynamicQueue {
    char **items;
    int front;
    int rear;
    int capacity;
};

void initDynamicQueue(struct DynamicQueue *queue, int capacity);

int isFullDynamic(struct DynamicQueue *queue);

int isEmptyDynamic(struct DynamicQueue *queue);

void enqueueDynamic(struct DynamicQueue *queue, const char *value);

char* dequeueDynamic(struct DynamicQueue *queue);



#endif /* INC_QUEUE_H_ */
