/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:09:51 by aaferyad          #+#    #+#             */
/*   Updated: 2025/08/09 16:02:08 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	lock_print(t_ph *philo, char *status)
{
	if (lock_mutex(&philo->data->print) != 0)
		return (1);
	if (!philo->data->end_simulation)
		print_status(status, philo);
	if (unlock_mutex(&philo->data->print) != 0)
		return (1);
	return (0);
}

int	philos_life(t_ph *philo)
{
	if (check_death(philo))
		return (1);
	if (philo->full)
		return (1);
	if (lock_print(philo, "is sleeping") != 0)
		return (1);
	if (check_death(philo))
		return (1);
	_usleep(philo->data->t_sleep, philo->data, philo);
	if (check_death(philo))
		return (1);
	if (lock_print(philo, "is thinking") != 0)
		return (1);
	return (0);
}

void	join_threads(t_sim *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
}

int	init_threads(t_sim *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		data->philos[i].id = i + 1;
		i++;
	}
	i = 0;
	while (i < data->n_philo)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				philo_cycle, &data->philos[i]) != 0)
		{
			full_cleanup(data);
			return (print_error_return("Could't create a thread", 1));
		}
		i++;
	}
	data->started = true;
	data->simulation_starts = _gettime();
	join_threads(data);
	return (0);
}

int	dinning(t_sim *data)
{
	if (init_threads(data))
		return (1);
	return (0);
}
