OBJS= shmem shread
CC=gcc
FLAGS=-lrt -Wall -o
PRE_FLAGS=-Wall -o

make: $(OBJS).o

# $(OBJS): $(OBJS).o
# 	$(CC) $@ $(FLAGS) $@

$(OBJS).o:$(OBJS).c
	echo $@.c