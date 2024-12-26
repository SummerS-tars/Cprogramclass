CFLAGS = -Wall
OBJ = menuUpdate.o 02_cursorOperation.o

all: menuUpdate

menuUpdate: $(OBJ)
	$(CC) $(CFLAGS) -o menuUpdate $(OBJ)

menuUpdate.o: menuUpdate.c menuUpdate.h 02_cursorOperation.h
	$(CC) $(CFLAGS) -c menuUpdate.c

02_cursorOperation.o: 02_cursorOperation.c 02_cursorOperation.h
	$(CC) $(CFLAGS) -c 02_cursorOperation.c

clean:
	rm -f *.o menuUpdate
