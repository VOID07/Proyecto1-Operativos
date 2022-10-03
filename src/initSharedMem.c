#include "../include/initSharedMem.h"

void initMem(int* mem_fd, int* chunk_fd, int* sem_fd){

    /* create the shared memory object */
    * mem_fd = shm_open("/sharedmem", O_CREAT | O_RDWR, 0666);
    * chunk_fd = shm_open("/chunkSize", O_CREAT | O_RDWR, 0666);
    * sem_fd = shm_open("/semaphore", O_CREAT | O_RDWR, 0666);
    
}
int main(int argc, char * argv[]){  // Name, num

    int mem_fd, chunk_fd, chunk_size, sem_fd;
    void* ptr_chunk, ptr_sem;

    initMem(&mem_fd, &chunk_fd, &sem_fd); // Pass value as reference to create the file descriptor
    chunk_size =  atoi(argv[1]); // Reads first parameter to load as chunk size
    ftruncate(chunk_fd, sizeof(chunk_size));
    ptr_chunk = mmap(0, sizeof(chunk_size), PROT_READ | PROT_WRITE, MAP_SHARED, chunk_fd, 0);
    sprintf(ptr_chunk, "%d", chunk_size); // Writes the chunk Size to shared memory
     shmat (int shmid, char * shmaddr, int shmflg)

    return 0;
    
}

// gcc shmem.c -o shared -Wall -lrt