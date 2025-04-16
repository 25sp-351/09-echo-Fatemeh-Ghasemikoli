# Makefile for TCP/HTTP Echo Server in C

CC = gcc
CFLAGS = -Wall -std=c11
TARGET = echo
OBJS = main.o server.o client_handler.o

all: format $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) -lpthread

main.o: main.c server.h
	$(CC) $(CFLAGS) -c main.c

server.o: server.c server.h client_handler.h
	$(CC) $(CFLAGS) -c server.c

client_handler.o: client_handler.c client_handler.h
	$(CC) $(CFLAGS) -c client_handler.c

clean:
	rm -f $(TARGET) $(OBJS)

format:
	@echo "Formatting C source files with clang-format..."
	clang-format -i *.c *.h
