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

time_t	_gettime(void)
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL))
		return (-1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	_usleep(time_t usec, t_sim *data, t_ph *philo)
{
	time_t	start;

	start = _gettime();
	if (start == -1)
		return (-1);
	while (_gettime() - start < usec)
	{
		if (data->end_simulation)
			return (1);
		if (start - philo->last_diner >= data->t_die)
		{
			lock_mutex(&data->end_simulation_mutex);
			data->end_simulation = true;
			unlock_mutex(&data->end_simulation_mutex);
			print_death(philo, _gettime());
			return (1);
		}
		usleep(100);
	}
	return (0);
}

int	destroy_mutex(t_sim *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		/*pthread_mutex_unlock(&data->forks[i].fork);*/
		/*pthread_mutex_unlock(&data->end_simulation_mutex);*/
		/*pthread_mutex_unlock(&data->print);*/
		pthread_mutex_destroy(&data->forks[i].fork);
		pthread_detach(data->philos[i].thread);
		i++;
	}
	pthread_mutex_destroy(&data->end_simulation_mutex);
	pthread_mutex_destroy(&data->print);
	return (0);
}

int	full_cleanup(t_sim *data)
{
	destroy_mutex(data);
	free(data->philos);
	free(data->forks);
	return (0);
}
int	print_error_return(char *error, int return_code)
{
	printf(RED"%s\n"RESET, error);
	return (return_code);
}

void	cleanup(t_sim *data)
{
	free(data->philos);
	free(data->forks);
}
