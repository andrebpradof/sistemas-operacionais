OBJS	= Memoria.o MemoriaVirtual.o Processo.o ,PaginaDeDisco.o main.o
SOURCE	= Memoria.cpp, MemoriaVirtual.cpp, Processo.cpp ,PaginaDeDisco.cpp, main.cpp
HEADER	= head.h, Memoria.h, MemoriaVirtual.h, PaginaDeDisco.h, Processo.h,
OUT	= trabalho_3.o
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

Memoria.o: Memoria.cpp,
	$(CC) $(FLAGS) Memoria.cpp, -std=c++98

MemoriaVirtual.o: MemoriaVirtual.cpp,
	$(CC) $(FLAGS) MemoriaVirtual.cpp, -std=c++98

Processo.o: Processo.cpp
	$(CC) $(FLAGS) Processo.cpp -std=c++98

,PaginaDeDisco.o: ,PaginaDeDisco.cpp,
	$(CC) $(FLAGS) ,PaginaDeDisco.cpp, -std=c++98

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp -std=c++98


clean:
	rm -f $(OBJS) $(OUT)