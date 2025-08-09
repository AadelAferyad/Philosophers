/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 15:35:24 by aaferyad          #+#    #+#             */
/*   Updated: 2025/08/09 15:55:34 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	check_death(t_ph *philo)
{
	long	current;

	current = _gettime();
	if (philo->data->n_simulation
		&& philo->diner_counter >= philo->data->n_simulation)
		philo->full = true;
	if (is_done(philo->data))
		return (1);
	if ((current - philo->last_diner > philo->data->t_die))
	{
		if (lock_mutex(&philo->data->end_simulation_mutex))
			return (1);
		philo->data->end_simulation = true;
		if (print_death(philo, current))
			return (1);
		if (unlock_mutex(&philo->data->end_simulation_mutex))
			return (1);
		return (1);
	}
	return (0);
}

time_t	_gettime(void)
{
	struct timeval	tv;

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
