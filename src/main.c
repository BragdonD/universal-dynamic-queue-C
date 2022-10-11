#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int main(int argc, char const *argv[])
{
    queue* q = queue_create_from_list((int[]){0,1,2,3,4,5,6,7,8,9}, 10, sizeof(int));
    for(int i=0; i<10; i++) {
        printf("%d\n", *(int*)queue_pop(q));
    }
    queue_free(q);
    return 0;
}
