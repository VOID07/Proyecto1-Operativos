#include "../include/memoryWraper.h"

struct pixel * shared_memory_ptr;
sem_t * shared_semaphore_ptr;
unsigned int * shared_chunk_size_ptr;
int mem_fd, 
    chunk_fd, 
    sem_fd,
    reader_fd,
    writer_fd;
int pointer = 0; // It is safe to asume the pointer start at 0 since there is only one process.

int push(struct pixel * pixel){
    return 0;
}


int pop(){
    return 0;
}

int init(){
    mem_fd=shm_open(SHARED_MEM, O_RDWR, 0666); // Opens a shared memory section
    chunk_fd=shm_open(SHARED_CHUNK_SIZE, O_RDWR, 0666);
    sem_fd=shm_open(SHARED_SEMAPHORE, O_RDWR, 0666);
    writer_fd=shm_open(SHARED_COUNTER_WRITE, O_RDWR, 0666);
    reader_fd=shm_open(SHARED_COUNTER_READ, O_RDWR, 0666);

    shared_memory_ptr = mmap(0, sizeof(struct pixel), PROT_READ, MAP_SHARED, mem_fd, 0);    // Maps the shared memory to the shared memory pointer
    shared_chunk_size_ptr = mmap(0, sizeof(int), PROT_READ, MAP_SHARED, chunk_fd, 0);    // Maps the shared memory to the semaphore pointer
    shared_semaphore_ptr = mmap(0, sizeof(sem_t), PROT_READ, MAP_SHARED, sem_fd, 0);    // Maps the shared memory to the semaphore pointer

    return 0;
}