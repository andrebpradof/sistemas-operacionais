OBJS	= Memoria.o MemoriaVirtual.o Processo.o PaginaDeDisco.o main.o
SOURCE	= Memoria.cpp MemoriaVirtual.cpp Processo.cpp PaginaDeDisco.cpp main.cpp
HEADER	= Head.h Memoria.h MemoriaVirtual.h PaginaDeDisco.h Processo.h
OUT	= memoria
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

Memoria.o: Memoria.cpp
	$(CC) $(FLAGS) Memoria.cpp 

MemoriaVirtual.o: MemoriaVirtual.cpp
	$(CC) $(FLAGS) MemoriaVirtual.cpp 

Processo.o: Processo.cpp
	$(CC) $(FLAGS) Processo.cpp 

PaginaDeDisco.o: PaginaDeDisco.cpp
	$(CC) $(FLAGS) PaginaDeDisco.cpp 

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp 
	
clean:
	rm -f *.o