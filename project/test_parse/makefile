CC = gcc

FLAGS = -c -g -Wall

LFLAGS = -lstring -labs -lgraph -lllist -lfdr -lbt -lparse -lio -lsocket -lconfig -lent

SRCS = $(wildcard *.c)

OBJS = $(SRCS:.c=.o)

PROGRAM = main

LIBS = -L../lib/implementation

INCLUDES = -I../lib/include

MYSQL = -I/usr/include/mysql

MFLAG = `mysql_config --cflags --libs`

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CC) -o $(PROGRAM) $(OBJS) $(INCLUDES) $(MYSQL) $(LIBS) $(LFLAGS) $(MFLAG)


.c.o: $(SRCS)
	$(CC) $(FLAGS) $(INCLUDES) $(MYSQL) $(SRCS)

clean:
	rm -rf core $(PROGRAM) $(OBJS) *~
