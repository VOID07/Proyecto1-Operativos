#include "../include/memoryWraper.h"

int main()
/* create the shared memory object */
    int mem_fd=shm_open("/sharedmem", O_CREAT | O_RDWR, 0666);
    /* configure the size of the shared memory object */
    ftruncate(mem_fd, sizeof(char)*100);
    /* pointer to shared memory object */
    void* ptr;
    /* memory map the shared memory object */
    ptr = mmap(0, sizeof(char)*100, PROT_READ | PROT_WRITE, MAP_SHARED, mem_fd, 0);