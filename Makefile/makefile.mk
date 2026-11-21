
CC=gcc
# прапори компілятора: -c лише компіляція, -Wall усі попередження, -I Header шлях до заголовків
CFLAGS=-c -Wall -I Header

all: lab6

# компонування об'єктних файлів у виконуваний файл
lab6: main.o lib.o
	$(CC) main.o lib.o -o lab6

# компіляція main.c в об'єктний файл
main.o: Source/main.c Header/lib.h
	$(CC) $(CFLAGS) Source/main.c

# компіляція lib.c в об'єктний файл
lib.o: Source/lib.c Header/lib.h
	$(CC) $(CFLAGS) Source/lib.c

# очищення проєкту від зайвих файлів
clean:
	rm -f *.o lab6

.PHONY: all clean