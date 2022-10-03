#include "../include/initSharedMem.h"

void initMem(int* mem_fd, const char * name){

    /* create the shared memory object */
    * mem_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    return;
}

int main(int argc, char * argv[]){  // Name, num

    int mem_fd, 
        chunk_fd, 
        chunk_size, 
        sem_fd,
        writer_fd,
        reader_fd;
    unsigned int* ptr_chunk_size;
    unsigned int* ptr_reader; // Shared counter for the encoder
    unsigned int* ptr_writer; // Shared counter for the decoder
    void* ptr_sem;
    
    chunk_size =  atoi(argv[1]); // Reads first parameter to load as chunk size

    initMem(&mem_fd, SHARED_MEM); // Pass value as reference to create the file descriptor
    initMem(&chunk_fd, SHARED_CHUNK_SIZE); // Pass value as reference to create the file descriptor
    initMem(&sem_fd, SHARED_SEMAPHORE); // Pass value as reference to create the file descriptor
    initMem(&writer_fd, SHARED_COUNTER_WRITE); // Pass value as reference to create the file descriptor
    initMem(&reader_fd, SHARED_COUNTER_READ); // Pass value as reference to create the file descriptor
    
    ftruncate(mem_fd, chunk_size*sizeof(struct pixel)); // Truncates to the size of the array 
    ftruncate(chunk_fd, sizeof(chunk_size)); // Truncates to the value of int
    ftruncate(writer_fd, sizeof(int)); // Truncates to the value of int
    ftruncate(reader_fd, sizeof(int)); // Truncates to the value of int
    ftruncate(sem_fd, sizeof(sem_t)); // Truncates to the  size of the semaphore

    ptr_sem = mmap(0, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED, sem_fd, 0);    // Maps the shared memory to the semaphore pointer
    ptr_chunk_size = mmap(0, sizeof(chunk_size), PROT_READ | PROT_WRITE, MAP_SHARED, chunk_fd, 0);    // Maps the shared memory to the semaphore pointer
    ptr_writer = mmap(0, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, writer_fd, 0);    // Maps the shared memory to the semaphore pointer
    ptr_reader = mmap(0, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, reader_fd, 0);    // Maps the shared memory to the semaphore pointer
    
    sem_init(&ptr_sem, 1, 1);  // Maps the semaphore to shared memory with chunk_size elements
    *ptr_chunk_size = chunk_size; // Writes the value of the chunk size to shared memory
    *ptr_writer = 0; // Writes the value of counter to shared memory
    *ptr_reader = 0; // Writes the value of counter to shared memory
    return 0;

}

// gcc shmem.c -o shared -Wall -lrt