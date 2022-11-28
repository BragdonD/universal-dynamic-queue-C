#include <stdlib.h>
#include "queue.h"

/// @brief Structure to create a queue element
typedef struct queue_elem {
    struct queue_elem* next;
    void* data;
} queue_elem;

queue_elem* queue_create_elem(void* data);

/// @brief Function to create and init a queue structure
/// @return a pointer toward the created queue
queue* queue_create() {
    queue* q = NULL;
    q = malloc(sizeof(*q));
    if(q == NULL) return NULL;
    q->front = NULL;
    q->end = NULL;
    q->length = 0;
    return q;
}

/// @brief Function to create a element to insert inside a queue
/// @param data the data to store inside the queue element
/// @return a pointer toward the queue element
queue_elem* queue_create_elem(void* data) {
    queue_elem* elem = NULL;
    elem = malloc(sizeof(*elem));
    if(elem == NULL) return NULL; ///Error to be handle in the caller function
    elem->data = data;
    elem->next = NULL;
    return elem;
}

/// @brief Function to add a element inside the queue
/// @param q a pointer toward a queue structure
/// @param elem a pointer toward the data to be inserted
/// @return true on success
bool queue_push(queue* q, void* elem) {
    queue_elem* new_elem = queue_create_elem(elem);
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

/// @brief Function to test if the queue is empty
/// @param q a pointer toward a queue structure
/// @return true or false
bool queue_empty(queue* q) {
    return q->length <= 0;
}

/// @brief Function to remove a element from the front of the queue
/// @param q a pointer toward a queue structure
/// @return a pointer toward the poped data
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

/// @brief Function to get the data store inside the front pointer of a queue
/// @param q a pointer toward a queue structure
/// @return a pointer toward the data store in the front pointer
void* queue_front(queue *q) {
    if(q == NULL || q->front == NULL) return NULL;
    return q->front->data;
}

/// @brief Function to get the data store inside the end pointer of a queue
/// @param q a pointer toward a queue structure
/// @return a pointer toward the data store in the end pointer
void* queue_end(queue *q) {
    if(q == NULL || q->end == NULL) return NULL;
    return q->end->data;
}

/// @brief Function to swap two queue
/// @param q1 the first queue structure
/// @param q2 the second queue structure
void queue_swap(queue* q1, queue* q2) {
    if(q1 == NULL || q2 == NULL) return;
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

/// @brief Function to get the size of a queue
/// @param q a pointer toward a queue structure
/// @return the size of the queue
size_t queue_size(queue* q) {
    if(q == NULL) return 0;
    return q->length;
}

/// @brief Function to free a queue structure
/// @param q a pointer toward a queue structure
/// @param free_data pointer function to free the data of the queue. Can be NULL if nothing needs to be free.
void queue_free(queue* q, void (*free_data)(void*)) {
    if(q == NULL) return;
    while(q->front != NULL) {
        if(free_data != NULL)
            free_data(queue_pop(q));
        queue_pop(q);
    }
    free(q);
}

/// @brief Function to create a queue from a list.
/// @param arr An array of elements
/// @param len the size of the array
/// @param type_size the data size
/// @return a pointer toward a queue structure.
queue* queue_create_from_list(void* arr, int len, size_t type_size) {
    queue* q = queue_create();
    if(q == NULL) return NULL;
    for(int i=0; i<len; i++) {
        queue_push(q,(((char*)arr) + (i) * type_size));
    }
    return q;
}