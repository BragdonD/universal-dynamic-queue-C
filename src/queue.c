#include <stdlib.h>
#include "queue.h"

typedef struct queue_elem {
    struct queue_elem* next;
    void* data;
} queue_elem;

queue_elem* create_queue_elem(void* data);

queue* queue_create() {
    queue* q = NULL;
    q = malloc(sizeof(*q));
    if(q == NULL) return NULL;
    q->front = NULL;
    q->end = NULL;
    q->length = 0;
    return q;
}

queue_elem* create_queue_elem(void* data) {
    queue_elem* elem = NULL;
    elem = malloc(sizeof(*elem));
    if(elem == NULL) return NULL; ///Error to be handle in the caller function
    elem->data = data;
    elem->next = NULL;
    return elem;
}

bool queue_push(queue* q, void* elem) {
    queue_elem* new_elem = create_queue_elem(elem);
    if(new_elem == NULL) return false;
    q->length += 1;
    if(q->end == NULL) {
        q->front = new_elem;
        q->end = new_elem;
        return true;
    }
    q->end->next = new_elem;
    q->end = new_elem;
    q->length += 1;
    return true;
}

bool queue_empty(queue* q) {
    return q->length <= 0;
}

void* queue_pop(queue* q) {
    queue_elem* front = NULL;
    void* data = NULL;
    if(queue_empty(q)) return NULL;
    q->length -= 1;
    front = q->front;
    data = front->data;
    q->front = q->front->next;
    free(front);
    return data;    
}

void* queue_front(queue *q) {
    return q->front->data;
}

void* queue_end(queue *q) {
    return q->end->data;
}

void queue_swap(queue* q1, queue* q2) {
    queue_elem *front = NULL, *end = NULL;
    size_t length = 0;
    front = q1->front;
    end = q1->front;
    length = q1->length;
    q1->front = q2->front;
    q1->end = q2->end;
    q1->length = q2->length;
    q2->front = front;
    q2->end = end;
    q2->length = length;
}

size_t queue_size(queue* q) {
    return q->length;
}

void queue_free(queue* q) {
    if(q == NULL) return;
    while(q->front != NULL) {
        queue_pop(q);
    }
    free(q);
}

queue* queue_create_from_list(void* arr, int len, size_t type_size) {
    queue* q = queue_create();
    if(q == NULL) return NULL;
    for(int i=0; i<len; i++) {
        queue_push(q,(((char*)arr) + (i) * type_size));
    }
    return q;
}