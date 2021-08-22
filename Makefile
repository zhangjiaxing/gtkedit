
CC=gcc
GTK_CFLAGS=`pkg-config --cflags gtk+-3.0`
GTK_LIBS=`pkg-config --libs gtk+-3.0`

CFLAGS+=$(GTK_CFLAGS)
LIBS+=$(GTK_LIBS)


gtkedit: gtkedit.c
	$(CC) ${CFLAGS} ${LIBS} -o $@ $^

all: gtkedit

.PHONY: clean

clean:
	rm -f *.o gtkedit

