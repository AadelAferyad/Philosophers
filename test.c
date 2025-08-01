#include "main.h"
#include <string.h>


char	buffer[10][100];
pthread_mutex_t	lock;

void	input_msg(char **av, int j)
{
	static	int i = 0;

	pthread_mutex_lock(&lock);
	printf("%d\n", j);
	while (i < 5)
	{
		strcpy(buffer[i], av[i]);
		i++;
	}
	pthread_mutex_unlock(&lock);
}

void	concat_msg(void)
{
	static	int i = 0;

	pthread_mutex_lock(&lock);
	while (i < 5)
	{
		strcat(buffer[i], " Good afternon");
		i++;
	}
	pthread_mutex_unlock(&lock);
}

int 	main(int ac, char **av)
{
	pthread_t	thread1;
	pthread_t	thread2;
	void	*status;
	struct timeval	tv;

	gettimeofday(&tv, NULL);

	printf("%ld\n", ((((tv.tv_sec + tv.tv_usec) / 60) / 60) / 24) / 365);
	/*pthread_mutex_init(&lock, NULL);*/
	/*pthread_create(&thread1, NULL, (void *)input_msg, (void *) (av + 1), 2);*/
	/*pthread_create(&thread2, NULL, (void *)concat_msg, NULL);*/
	/*pthread_join(thread1, &status);*/
	/*pthread_join(thread2, &status);*/
	/*for (int i = 0; i < 10; i++)*/
	/*	printf("%s\n", buffer[i]);*/
	return (0);
}

