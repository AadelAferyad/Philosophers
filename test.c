#include "main.h"


typedef struct t
{
	int	id;
	char	*b;
}test;


int 	main(void)
{
	test *p;

	p = allocation(5 * sizeof(test));
	for (int i = 0; i < 5; i++)
	{
		p[i].id = i + 1;
	}
	for (int i = 0; i < 5; i++)
	{
		printf(RED"id : %d\n"RESET, p[i].id);
		printf(GREEN"test\n"RESET);
	}
	free(p);
	return (0);
}

