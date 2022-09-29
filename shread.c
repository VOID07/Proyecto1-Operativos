#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <unistd.h>         /* Allows ftruncate*/
int main()
{   
    
    /* create the shared memory object */
    int mem_fd=shm_open("/sharedmem", O_CREAT | O_RDWR, 0666);
    /* configure the size of the shared memory object */
    ftruncate(mem_fd, sizeof(char)*100);
    /* pointer to shared memory object */
    void* ptr;
    /* memory map the shared memory object */
    ptr = mmap(0, sizeof(char)*100, PROT_READ | PROT_WRITE, MAP_SHARED, mem_fd, 0);

    /* strings written to shared memory */
    // const char* message_0 = "Hello";
    /* write to the shared memory object */
    printf("%s", (char*) ptr);

    __uint8_t a,b,c; 
    
    c=10111100
    
    c=a^b;
    return 0;
}


//gcc shread.c -o reader -Wall -lrt
// -lrt tag helps to link the shared memory libraries