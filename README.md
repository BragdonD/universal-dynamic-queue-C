### Dynamic-Queue in C

This is a dynamic queue implementation in C. It is able to store any kind of data. Note that if you pass pointer as type for the queue, you will need to handle the dealocation of the element each time you dequeue one.<br/>
Furthermore the queue is dynamic so it can grow.

## Folder-organisation

In the inc folder you will find the header for each files In the src folder you will find the implementation of all the function.
Here the `main` file is just mean as an utilization example.

## How to use it

First you will need to build the project, the makefile is provided with the program, so you just need to enter the following command at the racine of the workspace folder: mingw32-make. Ok so now, you have build the project, (the makefile is setup to compile the program for debug mode) you can now run the program by running the following once again at the racine of the workspace folder : .\bin\main.

In the program, you will be able to use multiple commands. They will be presented to you by a menu when the program is running.

### Create an empty queue
```c
int main() {
  queue* q = create_queue();
  queue_free(q, NULL); ///Need to be call to dealocate the memory !!!
  return 0;
}

```

### Create a queue from an array
```c
int main() {
  queue* q = queue_create_from_list((int[]){0,1,2,3,4,5,6,7,8,9}, 10, sizeof(int));
  queue_free(q, NULL); ///Need to be call to dealocate the memory !!!
  return 0;
}
```

## Warning

Please do not create the bin and obj folder. They will be created by the makefile. Plus do not touch to the created files inside those two folders.

### Free the memory
You need to call the function `queue_free(queue* q)` to dealocate memory at the end of the utilisation.
```c
int main() {
  queue* q = queue_create();
  queue_free(q, NULL); ///Need to be call to dealocate the memory !!!
  return 0;
}
```
#### Free memory + queue data is dynamic
If the data pass inside the queue is allocated dynamically you should avoid to call the function `queue_free(queue* q)`. Instead try something like:
```c
int main() {
  int *dynamic_int = malloc(sizeof(*dynamic_int));
  queue* q = queue_create();
  queue_push(dynamic_int);
  int len = queue_size(q);
  ///Part to dealocate the memory you allocate
  for(int i=0; i<len; i++){
    free(queue_pop(q));
  }
  queue_free(q, NULL); ///Call it to fully dealocate the q pointer.
  return 0;
}
```
