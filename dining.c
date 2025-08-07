/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dining.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:09:51 by aaferyad          #+#    #+#             */
/*   Updated: 2025/08/07 16:13:25 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	philos_life(t_ph *philo)
{
	pthread_mutex_lock(&philo->data->print);
	printf("%ld %d is sleeping\n", _gettime(), philo->id);
	pthread_mutex_unlock(&philo->data->print);
	_usleep(philo->data->t_sleep);
	pthread_mutex_lock(&philo->data->print);
	printf("%ld %d is thinking\n", _gettime(), philo->id);
	pthread_mutex_unlock(&philo->data->print);
}

void	eating(t_ph *philo)
{
	pthread_mutex_lock(&philo->main_fork->fork);
	pthread_mutex_lock(&philo->data->print);
	printf("%ld %d has taken a fork", _gettime(), philo->id);
	pthread_mutex_unlock(&philo->data->print);
	pthread_mutex_lock(&philo->next_fork->fork);
	pthread_mutex_lock(&philo->data->print);
	printf("%ld %d has taken a fork", _gettime(), philo->id);
	printf("%ld %d is eating\n", _gettime(), philo->id);
	philo->diner_counter++;
	philo->last_diner = _gettime();
	pthread_mutex_unlock(&philo->data->print);
	_usleep(philo->data->t_eat);
	pthread_mutex_unlock(&philo->main_fork->fork);
	pthread_mutex_unlock(&philo->next_fork->fork);
}

int	check_all_philo()

void	*philo_cycle(void *tmp)
{
	t_ph	*philo;

	philo = (t_ph *) tmp;
	/*while (!(*is_simulation_start()))*/
	/*	;*/
	philo->data->simulation_starts = _gettime();
	while (1)
	{
		philos_life(philo);
		eating(philo);
	}
	return (NULL);
}

int	init_threads(t_sim *data)
{
	int	i;
	/*int	*start;*/
	int	th;

	i = 0;
	while (++i <= data->n_philo)
		data->philos[i - 1].id = i;
	i = 0;
	while (i < data->n_philo)
	{
		if (pthread_create(&data->philos[i].thread, NULL, (void *) philo_cycle, &data->philos[i]) != 0)
		{
			full_cleanup(data);
			return (print_error_exit("Could't create a thread", 1));
		}
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	/*start = is_simulation_start();*/
	/**start = true;*/
	return (0);
}
int	dining(t_sim *data)
{
	if (init_threads(data))
		return (1); 
}
