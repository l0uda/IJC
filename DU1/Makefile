OPT=-O2
CFLAGS=-std=c11 -Wall -Wextra -pedantic

all: primes primes-i

run: primes primes-i
	ulimit -s 20000 && time ./primes
	ulimit -s 20000 && time ./primes-i

primes: primes.c eratosthenes.o bit_array.h eratosthenes.h
	gcc ${CFLAGS} ${OPT} eratosthenes.o primes.c -o primes -lm

primes-i: primes.c eratosthenes.o eratosthenes.h
	gcc ${CFLAGS} ${OPT} eratosthenes.o primes.c -o primes-i -DUSE_INLINE -lm

eratosthenes.o: eratosthenes.c eratosthenes.h
	gcc ${CFLAGS} ${OPT} -c eratosthenes.c

zip:
	zip xburda13.zip *.c *.h Makefile

clean:
	rm -f primes primes-i eratosthenes.o xburda13.zip
