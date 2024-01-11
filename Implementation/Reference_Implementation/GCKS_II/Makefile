INCDIR   := inc
SRCDIR   := src

CC=gcc

SOURCES= ./src/fips202.c ./src/NIST/rng.c ./src/pack.c  ./src/symmetric.c ./src/aes256ctr.c ./src/poly.c ./src/reduce.c ./src/sample.c ./src/sign.c
HEADERS= ./inc/api.h ./inc/fips202.h ./inc/NIST/rng.h ./inc/pack.h ./inc/symmetric.h ./inc/aes256ctr.h ./inc/poly.h ./inc/reduce.h ./inc/sample.h ./inc/sign.h ./inc/params.h

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



PQCgenKAT_sign: ./PQCgenKAT_sign.c
	$(CC) $(CFLAGS) -o $@ ./PQCgenKAT_sign.c $(HEADER) $(SOURCES) $(LDFLAGS)
	./PQCgenKAT_sign

debug:
	$(CC) $(DCFLAGS) -c  $(SOURCE) $(HEADER)
	$(CC) $(DCFLAGS) *.o -o debug_main $(LDFLAGS)
	#rm *.o
	./debug_main

.PHONY: clean

clean:
	rm PQCgenKAT_sign
	rm main
