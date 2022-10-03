#ifndef MEMORY_WRAPER_H
#define MEMORY_WRAPER_H

#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <unistd.h>         /* Allows ftruncate*/
#include <semaphore.h>      /* Allows the usage of the semaphore*/
#include "pixelStruct.h"
#include "ENV.h"

int push(struct pixel * );
int pop(struct pixel *);
int init();

#endif