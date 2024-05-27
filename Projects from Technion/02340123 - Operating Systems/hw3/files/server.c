//
// Created by student on 12/29/22.
//

#include <pthread.h>
#include <stdlib.h>

#include "segel.h"
#include "request.h"
#include "FIFO_queue.h"

#define REMOVED -1
#define BLOCK 1
#define DROP_TAIL 2
#define DROP_HEAD 3
#define DROP_RANDOM 4


//
// server.c: A very, very simple web server
//
// To run:
//  ./server <portnum (above 2000)>
//
// Repeatedly handles HTTP requests sent to this port number.
// Most of the work is done within routines written in request.c
//

// HW3: Parse the new arguments too

// STRUCT FOR THREADS STATS
typedef struct main_thread {
    pthread_t id;
    int total_req;
    int total_static;
    int total_dynamic;
} main_thread;


// ASSIST THREAD FUNCTION
void* assist_thread(void* arg);

// TWO QUEUES, ONE FOR WAITING, ONE FOR HANDLING
Queue* waiting_requests = NULL;
Queue* handling_requests = NULL;

pthread_cond_t empty_c;
pthread_cond_t full_c;
pthread_mutex_t m;

int threads_number = 0;
main_thread* threads_buff;

void getargs(int *port, int* queue_size, int* schedalg, int argc, char *argv[])
{
    if (argc < 5)
    {
        fprintf(stderr, "Usage: %s <port> <threads> <queue_size> <schedalg>\n", argv[0]);
        exit(1);
    }
    *port = atoi(argv[1]);
    threads_number=atoi(argv[2]);
    *queue_size=atoi(argv[3]);
    if(strcmp(argv[4], "block")==0)
    {
        *schedalg=BLOCK;
    }
    else if(strcmp(argv[4], "dt")==0)
    {
        *schedalg=DROP_TAIL;
    }
    else if(strcmp(argv[4], "dh")==0)
    {
        *schedalg=DROP_HEAD;
    }
    else if(strcmp(argv[4], "random")==0)
    {
        *schedalg=DROP_RANDOM;
    }
    else
    {
        fprintf(stderr, "Unknown overload policy");
        exit(1);
    }
}



int main(int argc, char *argv[])
{
    int listenfd, connfd, port, clientlen, queue_size, schedalg;
    struct sockaddr_in clientaddr;

    getargs(&port, &queue_size, &schedalg, argc, argv);

    // INITIALIZE THE QUEUES
    waiting_requests=initializeQueue();
    handling_requests=initializeQueue();

    // INITIALIZE THE MUTEX AND COND
    pthread_mutex_init(&m, NULL);
    pthread_cond_init(&full_c, NULL);
    pthread_cond_init(&empty_c, NULL);

    threads_buff = (main_thread*)malloc(sizeof(main_thread)*threads_number);
    for(int i=0; i<threads_number; i++)
    {
        threads_buff[i].total_req = 0;
        threads_buff[i].total_dynamic = 0;
        threads_buff[i].total_static = 0;
        pthread_create(&threads_buff[i].id, NULL, assist_thread, NULL);
    }
    listenfd = Open_listenfd(port);
    struct timeval curr_time;
    srand(time(NULL));

    while (1)
    {
        clientlen = sizeof(clientaddr);
        connfd = Accept(listenfd, (SA *) &clientaddr, (socklen_t *) &clientlen);

        pthread_mutex_lock(&m);

        // TIME OF ARRIVAL
        gettimeofday(&curr_time, NULL);
        struct timeval arrival_time = curr_time;

        int total_queues_size = getSize(waiting_requests) + getSize(handling_requests);
        if(total_queues_size >= queue_size) // queues are full, then wait
        {
            if(schedalg == BLOCK)
            {
                while(getSize(waiting_requests) + getSize(handling_requests) >= queue_size)
                {
                    pthread_cond_wait(&full_c, &m);
                }
            }
            else if(schedalg == DROP_TAIL)
            {
                Close(connfd);
                pthread_mutex_unlock(&m);
                continue;
            }
            else if(schedalg == DROP_HEAD)
            {
                if(getSize(waiting_requests) != 0)
                {
                    int curr_fd = waiting_requests->first->data->fd;
                    removeFromHead(waiting_requests);
                    Close(curr_fd);
                }
                else
                {
                    Close(connfd);
                    pthread_mutex_unlock(&m);
                    continue;
                }
            }
            else if(schedalg == DROP_RANDOM)
            {
                int currently_waiting = getSize(waiting_requests);
                if(currently_waiting == 0)
                {
                    Close(connfd);
                    pthread_mutex_unlock(&m);
                    continue;
                }
                if(currently_waiting == 1)
                {
                    int curr_fd = waiting_requests->first->data->fd;
                    removeFromHead(waiting_requests);
                    Close(curr_fd);
                }
                else
                {
                    int to_remove_size = (currently_waiting % 2 == 0) ? (currently_waiting/2) : ((int)(currently_waiting/2) + 1);
                    int* waiting_fds = (int*)malloc(sizeof(int)*currently_waiting);
                    int to_remove;
                    Node* head = waiting_requests->first;
                    for(int i=0 ; i<currently_waiting; i++)
                    {
                        waiting_fds[i] = head->data->fd;
                        head = head->next_node;
                    }
                    while(to_remove_size > 0)
                    {
                        to_remove = rand() % currently_waiting;
                        if(waiting_fds[to_remove] != REMOVED)
                        {
                            removeByID(waiting_requests, waiting_fds[to_remove]);
                            Close(waiting_fds[to_remove]);
                            waiting_fds[to_remove] = REMOVED;
                            to_remove_size--;
                        }
                    }
                    free(waiting_fds);
                }
            }
        }
        insertInQueue(waiting_requests, connfd, arrival_time);
        pthread_cond_signal(&empty_c);
        pthread_mutex_unlock(&m);
    }
}

void* assist_thread(void* arg)
{
    struct timeval curr_time;
    while(1)
    {
        pthread_mutex_lock(&m);

        while (getSize(waiting_requests) == 0) {
            pthread_cond_wait(&empty_c, &m);
        }
        gettimeofday(&curr_time, NULL);

        struct timeval picked_time = curr_time;
        int curr_fd = waiting_requests->first->data->fd, thread_id=0;
        struct timeval arrival_time = waiting_requests->first->data->arrival_time;
        struct timeval dispatch_time;
        timersub(&picked_time, &arrival_time, &dispatch_time);
        moveBetweenQueues(waiting_requests, handling_requests);

        pthread_t this_id = pthread_self();
        while (thread_id < threads_number) {
            if(this_id == threads_buff[thread_id].id)
                break;
            thread_id++;
        }

        pthread_mutex_unlock(&m);

        int res = requestHandle(curr_fd, thread_id, arrival_time, dispatch_time, threads_buff[thread_id].total_req,
                                threads_buff[thread_id].total_dynamic, threads_buff[thread_id].total_static);

        Close(curr_fd); // Close the fd since we are done

        // Now we will remove it from the queue and update our counters, so we will lock
        pthread_mutex_lock(&m);

        threads_buff[thread_id].total_req++;
        if(res == STATIC)
            threads_buff[thread_id].total_static++;
        else if(res == DYNAMIC)
            threads_buff[thread_id].total_dynamic++;
        removeByID(handling_requests, curr_fd);
        pthread_cond_signal(&full_c); // We can add more requests

        pthread_mutex_unlock(&m); // Unlock since we are done
    }
}