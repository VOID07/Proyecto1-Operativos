#include "../include/memoryWraper.h"

struct pixel * shared_memory_ptr;
sem_t * shared_semaphore_ptr;
int * shared_chunk_size_ptr;
int * writer_ptr;
int * reader_ptr;

int mem_fd, 
    chunk_fd, 
    sem_fd,
    reader_fd,
    writer_fd;

int push(struct pixel * pixel){
    sem_wait(shared_semaphore_ptr);
    *(shared_memory_ptr + *writer_ptr) = *pixel;
    *writer_ptr = (*writer_ptr + 1)%(*shared_chunk_size_ptr);
    sem_post(shared_semaphore_ptr);
    return 0;
}


int pop(struct pixel * out_pixel){
    sem_wait(shared_semaphore_ptr); 
    *out_pixel = *(shared_memory_ptr + *reader_ptr);
    *reader_ptr = (*reader_ptr + 1)%(*shared_chunk_size_ptr);
    sem_post(shared_semaphore_ptr);
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
    shared_semaphore_ptr = mmap(0, sizeof(sem_t), PROT_READ, MAP_SHARED, sem_fd, 0);  
    writer_ptr = mmap(0, sizeof(int), PROT_READ, MAP_SHARED, writer_fd, 0); 
    reader_ptr = mmap(0, sizeof(int), PROT_READ, MAP_SHARED, reader_fd, 0);   // Maps the shared memory to the semaphore pointer

    return 0;
}