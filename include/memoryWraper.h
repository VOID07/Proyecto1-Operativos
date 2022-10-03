#ifndef MEMORY_WRAPER_H
#define MEMORY_WRAPER_H

#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <unistd.h>         /* Allows ftruncate*/

void initMem();
int main();

#endif