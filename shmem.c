#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <unistd.h>         /* Allows ftruncate*/

#include <time.h>

int main()
{   
    
    /* create the shared memory object */
    int mem_fd=shm_open("/asdf", O_CREAT | O_RDWR,0666);
    /* configure the size of the shared memory object */
    ftruncate(mem_fd, sizeof(char)*100);
    /* pointer to shared memory object */
    void* ptr;
    /* memory map the shared memory object */
    ptr = mmap(0, sizeof(char)*100, PROT_READ | PROT_WRITE, MAP_SHARED, mem_fd, 0);

    /* strings written to shared memory */
    const char* message_0 = "Hello\n";
    /* write to the shared memory object */
    sprintf(ptr, "%s", message_0);
    
    int nuim;
    clock_t  start, end;
    start = clock();
    scanf("%d", &nuim);  
    end = clock();
    shm_unlink("/asdf");
    double ticks = (double)(end - start) / (double)(CLOCKS_PER_SEC);
    printf("El proceso tardo %lf. \n", ticks);
    return 0;
}
// gcc shmem.c -o shared -Wall -lrt
// -lrt tag helps to link the shared memory libraries