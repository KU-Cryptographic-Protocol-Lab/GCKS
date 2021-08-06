INCDIR   := inc
SRCDIR   := src

CC=gcc

SOURCE = main.c ./src/*.c  ./$(SRCDIR)/NIST/*.c 

HEADER = -I./$(INCDIR) -I./$(INCDIR)/NIST
CFLAGS  = -march=native -mtune=native -O3 -fomit-frame-pointer
LDFLAGS = -lcrypto
DFLAGS  = -g3 -DDEBUG



	
ALL:
	$(CC) $(CFLAGS) -c  $(SOURCE) $(HEADER)
	$(CC) $(CFLAGS) *.o -o main $(LDFLAGS)
	#rm *.o
	./main	

debug:
	$(CC) $(DCFLAGS) -c  $(SOURCE) $(HEADER)
	$(CC) $(DCFLAGS) *.o -o debug_main $(LDFLAGS)
	#rm *.o
	./debug_main