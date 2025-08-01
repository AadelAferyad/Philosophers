/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 13:51:28 by aaferyad          #+#    #+#             */
/*   Updated: 2025/07/30 18:58:41 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	thining(int philos_id)
{
	printf("philospher %d: thinking\n", philos_id);
}

void	sleeping(int philos_id)
{
	printf("philospher %d: is sleeping %d\n", philos_id, *get_time_to_sleep());
	usleep(*get_time_to_sleep());
}

void	eating(ph *philo)
{
	pthread_mutex_lock(&philo->main_fork->fork);
	pthread_mutex_lock(&philo->next_fork->fork);
	printf("philospher %d: is eating\n", philo->id);
	usleep(*get_time_to_eat());
	pthread_mutex_unlock(&philo->main_fork->fork);
	pthread_mutex_unlock(&philo->next_fork->fork);
}

void	*philo_cycle(void *tmp)
{
	ph	*philo;

	philo = (ph *) tmp;
	while (!(*is_simulation_start()))
		;
	while (1)
	{
		thining(philo->id);
		sleeping(philo->id);
		eating(philo);
	}
	return (NULL);
}

void	init_threads(simulation *data)
{
	int	i;
	int	*start;
	int	th;

	i = 0;
	while (++i <= data->n_philo)
		data->philo[i - 1].id = i;
	i = 0;
	while (i < data->n_philo)
	{
		th = pthread_create(&data->philo[i].thread, NULL, (void *) philo_cycle, &data->philo[i]);
		if (th != 0)
		{
			cleanup(data);
			print_error("Could't create a thread\n");
		}
		i++;
	}
	start = is_simulation_start();
	*start = true;
}

void	init_forks(simulation *data)
{
	int	i;

	i = 0;
	data->fork = allocation(data->n_philo * sizeof(forks));
	while (i < data->n_philo)
	{
		data->fork[i].fork_id = i + 1;
		pthread_mutex_init(&data->fork[i].fork, NULL);
		i++;
	}
}
/*
 * [1|2|3|4|5]
 * [1|2|3|4|5]
 * */
void	init_pointer(simulation *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		data->philo[i].main_fork = &data->fork[i];
		if (i + 1 < data->n_philo)
			data->philo[i].next_fork = &data->fork[i + 1];
		else
			data->philo[i].next_fork = &data->fork[0];
		i++;
	}
}

void	init(simulation *data)
{
	int	i;

	data->philo = allocation(data->n_philo * sizeof(ph));
	init_threads(data);
	init_forks(data);
	init_pointer(data);
}
