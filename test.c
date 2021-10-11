#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

typedef struct s_test
{
	sem_t	counter;
}			test;

int main(int argc, char**argv)
{
	int fo;
	int tester;
	test te;

	fo = fork();
	tester = 10;
	te.counter = 0;
	if (fo == 0)
	{
		tester++;
		te.counter++;
	}
	printf("tester = %d --- counter = %d\n", tester, te.counter);
}