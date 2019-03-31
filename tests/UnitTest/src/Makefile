VPATH:=../src
# Declaration of variables
TARGET = unittest
CC := gcc
CC_FLAGS = -Wall
#PATH=/home/deepesh/buildroot/buildroot/output/host/usr/bin:$PATH
#file names 
SOURCES = $(wildcard *.c)
INCLUDES:=-I ../inc/
OBJECTS = $(SOURCES:.c=.o)
LIBS:= -lcunit -lpthread -lrt -lm

#main target
build: $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(INCLUDES) $(LIBS)

#to obtain object files
%.o: %.c
	$(CC) -c $(CC_FLAGS) $^ -o $@ $(INCLUDES) $(LIBS)

# clean
clean:
	rm -rf $(TARGET) $(OBJECTS)
