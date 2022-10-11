#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

typedef struct queue_elem queue_elem;

typedef struct queue {
    queue_elem* front;
    queue_elem* end;
    size_t length;
} queue;

queue* queue_create();
queue* queue_create_from_list(void* arr, int len, size_t type_size);
bool queue_push(queue* q, void* elem);
void* queue_pop(queue* q);
bool queue_empty(queue* q);
void* queue_front(queue *q);
void* queue_end(queue *q);
void queue_swap(queue* q1, queue* q2);
size_t queue_size(queue* q);
void queue_free(queue* q);

#endif