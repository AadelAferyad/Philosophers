/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 13:51:28 by aaferyad          #+#    #+#             */
/*   Updated: 2025/08/07 14:57:36 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	assign_forks(t_ph *philo, t_forks *forks, int pos)
{
	int	n_ph;

	n_ph = philo->data->n_philo;
	philo->main_fork = &forks[(pos + 1) % n_ph];
	philo->next_fork = &forks[pos];
	if (philo->id % 2 == 0)
	{
		philo->main_fork = &forks[pos];
		philo->next_fork = &forks[(pos + 1) % n_ph];
	}
}

static void	init_philo(t_sim *data)
{
	int	i;
	t_ph	*philo;

	i = 0;
	while (i < data->n_philo)
	{
		philo = data->philos + i;
		philo->id = i + 1;
		philo->full = 0;
		philo->diner_counter = 0;
		philo->data = data;
		assign_forks(philo, data->forks, i);
		i++;
	}

}

int	init_forks(t_sim *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		data->forks[i].fork_id = i + 1;
		if (pthread_mutex_init(&data->forks[i].fork, NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&data->forks[i].fork);
			return (1);
		}

		i++;
	}
	return (0);
}

int	init(t_sim *data)
{
	data->end_simulation = false;
	if (pthread_mutex_init(&data->end_simulation_mutex, NULL) != 0)
	{
		cleanup(data);
		return (1);
	}
	data->philos = malloc(data->n_philo * sizeof(t_ph));
	if (!data->philos)
		print_error_exit("malloc failed");
	data->forks = malloc(data->n_philo * sizeof(t_forks));
	if (!data->philos)
	{
		free(data->philos);
		print_error_exit("malloc failed");
	}
	if (init_forks(data))
	{
		cleanup(data);
		return (1);
	}
	init_philo(data);
	return (0);
}
