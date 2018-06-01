CC = gcc

FLAGS = -c -g -Wall

LFLAGS = -lstring -labs -lgraph -lllist -lfdr -lbt -lauth -lparse -lmessage -lclient -lserver -lio -lsocket -lconfig -lent
#testing LFLAGS because of orders
SRCS = $(wildcard *.c)

OBJS = $(SRCS:.c=.o)

PROGRAM = main

LIBS = -L../lib/implementation

INCLUDES = -I../lib/include

INCLUDES_PRO = -I../program/include

LIBS_PRO = -L../program/implementation

MYSQL = -I/usr/include/mysql

MFLAG = `mysql_config --cflags --libs`

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CC) -o $(PROGRAM) $(OBJS) $(INCLUDES) $(MYSQL) $(INCLUDES_PRO) $(LIBS) $(LIBS_PRO) $(LFLAGS) $(MFLAG)


.c.o: $(SRCS)
	$(CC) $(FLAGS) $(INCLUDES) $(INCLUDES_PRO) $(MYSQL) $(SRCS)

clean:
	rm -rf core $(PROGRAM) $(OBJS) *~
