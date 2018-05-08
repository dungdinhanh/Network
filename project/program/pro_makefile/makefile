CC = gcc

FLAGS = -c -g -Wall

LFLAGS = -lstring -labs -lgraph -lllist -lfdr -lbt -lparse -lio -lsocket -lconfig -lent

SRCS = $(wildcard *.c)

OBJS = $(SRCS:.c=.o)

HEADER = $(wildcard *.h)

HEADFOLDER = libabc

PROGRAM = $(HEADFOLDER).a

LIBS = -L../../lib/implementation

INCLUDES = -I../../lib/include

LIBS_PRO = -L../implementation/

INCLUDES_PRO = -I../include/

MYSQL = -I/usr/include/mysql

MFLAG = `mysql_config --cflags --libs`

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	ar ru $(LIBS_PRO)$(PROGRAM) $(OBJS)
	ranlib $(LIBS_PRO)$(PROGRAM)
	mkdir $(INCLUDES_PRO)$(HEADFOLDER)
	cp $(HEADER) $(INCLUDES_PRO)$(HEADFOLDER)


.c.o: $(SRCS)
	$(CC) $(FLAGS) $(INCLUDES) $(MYSQL) $(SRCS)

clean:
	rm -rf core $(LIBS_PRO)$(PROGRAM) $(INCLUDES_PRO)$(HEADFOLDER) $(OBJS) *~