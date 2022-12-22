OBJS	= main.o
SOURCE	= main.cpp
HEADER	= utilidades.h metodos.h
OUT		= tarea
CC	 	= g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: clean main.o
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp -std=c++14


clean:
	@echo " [CLN] Removing binary files"
	@rm -f $(OBJS) $(OUT)