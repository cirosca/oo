all: programma test_runner

programma: main.c item.c segnalazione.c hash.c
	gcc main.c item.c segnalazione.c hash.c -o programma

test_runner: test.c item.c segnalazione.c hash.c
	gcc test.c item.c segnalazione.c hash.c -o test_runner

clean:
	rm programma test_runner