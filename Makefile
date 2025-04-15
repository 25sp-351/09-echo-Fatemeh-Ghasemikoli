# Makefile for TCP Echo Server

CXX = g++
CXXFLAGS = -Wall -std=c++11
TARGET = echo
OBJS = main.o server.o client_handler.o

all: format $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp server.h
	$(CXX) $(CXXFLAGS) -c main.cpp

server.o: server.cpp server.h
	$(CXX) $(CXXFLAGS) -c server.cpp

client_handler.o: client_handler.cpp client_handler.h
	$(CXX) $(CXXFLAGS) -c client_handler.cpp
	
clean:
	rm -f $(TARGET) $(OBJS)

format:
	@echo "Formatting source files with clang-format..."
	clang-format -i *.cpp *.h
