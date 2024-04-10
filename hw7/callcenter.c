#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>

int main(int argc, char **argv)
{
	int num_agents = 2;
	if (argc > 1)
		num_agents = atoi(argv[1]);
	printf("Starting a call center with %d agents.\n", num_agents);

	//
	// OS -- CRAETE NAMED SEMAPHORE HERE
	//
	sem_t *sem = sem_open("callcenter", O_CREAT, 0644, num_agents);

	int semval;
	while (1)
	{

		//
		// OS -- PLACE CURRENT VALUE OF SEMAPHORE IN 'semval' HERE
		//
		sem_getvalue(sem, &semval);

		printf("There are %d agents available now.\n", semval);
		sleep(3);
	}
}
