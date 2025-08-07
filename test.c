#include "main.h"
#include <string.h>

long	_gettime(void)
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL))
		return (-1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	_usleep(long usec)
{
	long	start;

	start = _gettime();
	if (start == -1)
		return (-1);
	while (_gettime() - start < usec)
		usleep(100);
	return (0);
}

int	main(void)
{
	_usleep(1000);
	return (0);
}
