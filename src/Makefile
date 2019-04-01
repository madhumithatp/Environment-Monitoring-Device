VPATH:=../src
# Declaration of variables
PLATFORM = BBG
TARGET = project01

ifeq ($(PLATFORM),HOST)
        CC := gcc
endif

ifeq ($(PLATFORM),BBG)
        CC := arm-linux-gcc
endif

CC_FLAGS = -w -g
PATH=/home/deepesh/buildroot/buildroot/output/host/usr/bin:$PATH
#file names 
SOURCES = $(wildcard *.c)
INCLUDES:=-I../inc/
OBJECTS = $(SOURCES:.c=.o)
LIBS= -lpthread -lrt -lm

#main target
build: $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(INCLUDES)

run : build
ifeq ($(PLATFORM),BBG)
	/usr/bin/scp $(TARGET) root@192.168.0.2:/home/project01/$(TARGET)
        #ssh -t root@192.168.0.2 "cd /home/project01/ && gdbserver localhost:4000 target"
else
        ./$(TARGET)
endif

#to obtain object files
%.o: %.c
	$(CC) -c $(CC_FLAGS) $^ -o $@ $(LIBS) $(INCLUDES)

# clean
clean:
	rm -rf $(TARGET) $(OBJECTS)
