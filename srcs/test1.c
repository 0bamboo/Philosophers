
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details.
#include <pthread.h>
  
void *test_1()
{
	printf("from thread 1\n");
}

void *test_2()
{
	printf("from thread 2\n");
}

int main()
{
	pthread_t t1, t2;
	pthread_create(&t2, NULL, &test_2, NULL);
	pthread_create(&t1, NULL, &test_1, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	return (0);
}