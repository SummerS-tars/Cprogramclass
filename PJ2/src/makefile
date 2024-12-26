CC = gcc
CFLAGS = -Wall
OBJ = 00_main.o 01_menuUpdate.o 02_cursorOperation.o 03_mapAndPlayerStatus.o 04_mapCustom.o

all: main

main: $(OBJ)
	$(CC) $(CFLAGS) -o main $(OBJ)

00_main.o: 00_main.c 01_menuUpdate.h 02_cursorOperation.h 03_mapAndPlayerStatus.h 04_mapCustom.h
	$(CC) $(CFLAGS) -c 00_main.c

01_menuUpdate.o: 01_menuUpdate.c 01_menuUpdate.h 02_cursorOperation.h 03_mapAndPlayerStatus.h 04_mapCustom.h
	$(CC) $(CFLAGS) -c 01_menuUpdate.c

02_cursorOperation.o: 02_cursorOperation.c 02_cursorOperation.h
	$(CC) $(CFLAGS) -c 02_cursorOperation.c

03_mapAndPlayerStatus.o: 03_mapAndPlayerStatus.c 03_mapAndPlayerStatus.h 02_cursorOperation.h 01_menuUpdate.h
	$(CC) $(CFLAGS) -c 03_mapAndPlayerStatus.c

04_mapCustom.o: 04_mapCustom.c 04_mapCustom.h 02_cursorOperation.h 03_mapAndPlayerStatus.h 01_menuUpdate.h
	$(CC) $(CFLAGS) -c 04_mapCustom.c

clean:
	rm -f *.o main
