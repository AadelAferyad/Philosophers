/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 13:52:03 by aaferyad          #+#    #+#             */
/*   Updated: 2025/08/07 15:31:49 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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

int	full_cleanup(t_sim *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_destroy(&data->forks[i].fork);
		pthread_detach(data->philos[i].thread);
		i++;
	}
	pthread_mutex_destroy(&data->end_simulation_mutex);
	free(data->philos);
	free(data->forks);
	return (1);
}
int	print_error_exit(char *error, int exit_code)
{
	printf(RED"%s\n"RESET, error);
	return (exit_code);
}

void	cleanup(t_sim *data)
{
	free(data->philos);
	free(data->forks);
}
