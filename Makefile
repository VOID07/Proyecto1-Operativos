OBJS= shmem shread
CC=gcc
FLAGS=-lrt -Wall -o
PRE_FLAGS=-Wall -o
INCLUDE="/mnt/d/Users/RED/Documents/TEC/Semestre 2 - 2022/Operativos/Proyecto1/include"
make: $(OBJS).o

# $(OBJS): $(OBJS).o
# 	$(CC) $@ $(FLAGS) $@

$(OBJS).o:$(OBJS).c
	echo $@.c