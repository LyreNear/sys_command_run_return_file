#!Makefile

C_SOURCES = $(shell find . -name "*.c")
C_OBJECTS = $(patsubst %.c, %.o, $(C_SOURCES))
S_SOURCES = $(shell find . -name "*.s")
S_OBJECTS = $(patsubst %.s, %.o, $(S_SOURCES))

CC = gcc
LD = ld
ASM = nasm

C_FLAGS = -c -Wall -I include
LD_FLAGS = -lpthread
ASM_FLAGS =

all: $(S_OBJECTS) $(C_OBJECTS) link

.c.o:
	@echo compile file $< ...
	$(CC) $(C_FLAGS) $< -o $@

.s.o:
	@echo assemble file $< ...
	$(ASM) $(ASM_FLAGS) $<

link:
	@echo link file...
	$(CC) $(S_OBJECTS) $(C_OBJECTS) $(LD_FLAGS) -o sys_command_run_return_file

.PHONY:clean
clean:
	$(RM) $(S_OBJECTS) $(C_OBJECTS) file_search
