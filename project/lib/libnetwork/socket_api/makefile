CC = gcc

FLAGS = -c -g -Wall

LFLAGS = -lstring -labs -lgraph -llist -lfdr - lbt

SRCS = $(wildcard *.c)

HEADER = $(wildcard *.h)

HEADFOLDER = libsocket

OBJS = $(SRCS:.c=.o)

PROGRAM = libsocket.a

LIBS = ../../implementation/

INCLUDES = ../../include


all: $(PROGRAM)

$(PROGRAM): $(OBJS)
		ar ru $(LIBS)$(PROGRAM) $(OBJS)
		ranlib $(LIBS)$(PROGRAM)
		mkdir $(INCLUDES)/$(HEADFOLDER)
		cp $(HEADER) $(INCLUDES)/$(HEADFOLDER)

.c.o: $(SRCS)
		$(CC) $(FLAGS) -I$(INCLUDES) $(SRCS)

clean:
		rm -rf core $(LIBS)$(PROGRAM) $(OBJS) $(INCLUDES)/$(HEADFOLDER) *~