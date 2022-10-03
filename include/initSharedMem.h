#ifndef INIT_SHARED_MEM_H
#define INIT_SHARED_MEM_H

#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <unistd.h>         /* Allows ftruncate*/
#include <time.h>
#include <semaphore.h>      /* Allows the usage of the semaphore*/
#include "pixelStruct.h"
#include "ENV.h"

void initMem(int*, const char* );
int main(int, char **);

#endif