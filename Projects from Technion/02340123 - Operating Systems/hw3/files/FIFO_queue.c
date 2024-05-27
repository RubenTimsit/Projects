#include <stdio.h>
#include <stdlib.h>
#include "FIFO_queue.h"


Queue* initializeQueue()
{
    Queue* queue= (Queue*)malloc(sizeof(Queue));
    queue->first=NULL;
    return queue;
}

int getSize(Queue* queue)
{
    int size=0;
    Node* current=queue->first;
    while(current!=NULL)
    {
        size++;
        current=current->next_node;
    }
    return size;
}

void insertInQueue(Queue* queue, int fd, struct timeval arrival_t)
{
    Node* newNode;
    newNode=(Node*)malloc(sizeof(Node));
    newNode->data=(Data*)malloc(sizeof(Data));
    newNode->data->fd=fd;
    newNode->data->arrival_time=arrival_t;
    newNode->next_node=NULL;

    if(queue->first == NULL)
    {
        queue->first=newNode;
        return;
    }
    Node* curr = queue->first;
    while(curr->next_node != NULL)
        curr=curr->next_node;
    curr->next_node=newNode;

}

void removeFromHead(Queue* queue)
{
    if(getSize(queue)==0)
    {
        return;
    }
    else
    {
        Node* to_delete=queue->first;
        queue->first=to_delete->next_node;
        free(to_delete->data);
        free(to_delete);
    }
}

void removeByID(Queue* queue, int fd)
{
    if(queue->first==NULL)
    {
        return;
    }

    Node* prev=queue->first;
    Node* current=prev->next_node;

    if(prev->data->fd == fd)
    {
        queue->first=current;
        free(prev->data);
        prev->next_node=NULL;
        free(prev);
        return;
    }
    while(current != NULL) {
        if (current->data->fd == fd) {
            prev->next_node = current->next_node;
            current->next_node = NULL;
            free(current->data);
            free(current);
            return;
        }
        prev = current;
        current = current->next_node;
    }
}

void moveBetweenQueues(Queue* source, Queue* dest)
{
    if(getSize(source)==0)
    {
        return;
    }
    Node* to_move=source->first;

    // Update SRC queue
    source->first=to_move->next_node;

    // Update DEST queue
    if(getSize(dest)==0)
    {
        dest->first=to_move;
    }
    else
    {
        Node* curr= dest->first;
        while(curr->next_node != NULL)
            curr=curr->next_node;
        curr->next_node=to_move;
    }
    to_move->next_node=NULL;
}