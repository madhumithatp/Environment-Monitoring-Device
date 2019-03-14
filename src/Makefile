VPATH:=../src
# Declaration of variables
CC = gcc
CC_FLAGS = -w -g

#file names 
EXEC = target
SOURCES = $(wildcard *.c)
INCLUDES:=-I../inc/
OBJECTS = $(SOURCES:.c=.o)
LIBS= -lpthread -lrt -lm

#main target
$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC) $(INCLUDES)

#to obtain object files
%.o: %.c
	$(CC) -c $(CC_FLAGS) $^ -o $@ $(LIBS) $(INCLUDES)

# clean
clean:
	rm -rf $(EXEC) $(OBJECTS)
