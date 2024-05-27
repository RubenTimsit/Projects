//
// Created by student on 12/29/22.
//

#ifndef OS_HW3_FIFO_QUEUE_H
#define OS_HW3_FIFO_QUEUE_H

typedef struct data_in_node {
    int fd;
    struct timeval arrival_time;
} Data;

typedef struct Node {
    Data* data;
    struct Node* next_node;
} Node;

typedef struct Queue {
    Node* first;
} Queue;

Queue* initializeQueue();
int getSize(Queue* queue);
void insertInQueue(Queue* queue, int fd, struct timeval arrival_t);
void removeFromHead(Queue* queue);
void removeByID(Queue* queue, int fd);
void moveBetweenQueues(Queue* source, Queue* dest);


#endif //OS_HW3_FIFO_QUEUE_H
