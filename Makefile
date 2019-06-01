CC= g++
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
CFLAGS = -Wall -g -std=c++11
EXEC = sudoku
DEPS = board.h cabecera.h
OBJS = board.o cabecera.o main.o
SRCS =  $(OBJS:.o=.cpp)

.PHONY: all clean doc

all: $(EXEC) #doc

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -g $< -o $@

$(EXEC):  $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(EXEC)

clean:
	$(RM) $(EXEC) $(EXEC).o $(OBJS)

doc: $(SRCS)
	doxygen
