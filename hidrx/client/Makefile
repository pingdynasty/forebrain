TARGET = hidclient
CSRC = hid.c
CPPSRC = hidclient.cpp
LDFLAGS = -framework IOKit -framework CoreFoundation

CC = gcc
CPP = g++
REMOVE = rm -f

OBJ = $(CSRC:.c=.o) $(CPPSRC:.cpp=.o) $(ASRC:.S=.o) 

all: $(TARGET)

.cpp.o:
	$(CPP) -c $(ALL_CPPFLAGS) $< -o $@ 

.c.o:
	$(CC) -c $(ALL_CFLAGS) $< -o $@ 

$(TARGET): $(OBJ)
	g++ -Wall -g $(OBJ) $(LDFLAGS) -o $@

clean:
	$(REMOVE) $(TARGET)  \
	$(OBJ) $(CSRC:.c=.s) $(CSRC:.c=.d) $(CPPSRC:.cpp=.s) $(CPPSRC:.cpp=.d)
