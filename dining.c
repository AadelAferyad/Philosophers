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


int	print_status(char *status, t_ph *philo)
{
	long	current;
	long	start;

	current = _gettime();
	start = philo->data->simulation_starts;
	printf("%ld %d %s\n", current - start, philo->id, status);
	return (0);
}

int	lock_mutex(pthread_mutex_t *lock)
{
	if (!lock)
		return (1);
	return (pthread_mutex_lock(lock));
}

int	unlock_mutex(pthread_mutex_t *lock)
{
	if (!lock)
		return (1);
	return (pthread_mutex_unlock(lock));
}

int	print_death(t_ph *philo, long current)
{
	long	start;

	start = philo->data->simulation_starts;
	if (lock_mutex(&philo->data->print) != 0)
		return (1);
	printf(RED"%ld %d died\n"RESET, current - start, philo->id);
	if (unlock_mutex(&philo->data->print) != 0)
		return (1);
	return (0);
}

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

int 	philos_life(t_ph *philo)
{
	if (check_death(philo))
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

int	eating(t_ph *philo)
{
	if (check_death(philo))
		return (1);
	if (lock_mutex(&philo->main_fork->fork) != 0)
		return (1);
	if (lock_print(philo, "has taken a fork") != 0)
		return (1);
	if (lock_mutex(&philo->next_fork->fork) != 0)
		return (1);
	if (lock_print(philo, "has taken a fork") != 0)
		return (1);
	if (lock_print(philo, "is eating") != 0)
		return (1);
	if (check_death(philo))
	{
		unlock_mutex(&philo->main_fork->fork);
		unlock_mutex(&philo->next_fork->fork);
		return (1);
	}
	philo->last_diner = _gettime();
	_usleep(philo->data->t_eat, philo->data, philo);
	if (check_death(philo))
	{
		unlock_mutex(&philo->main_fork->fork);
		unlock_mutex(&philo->next_fork->fork);
		return (1);
	}
	philo->diner_counter++;
	if (unlock_mutex(&philo->main_fork->fork) != 0)
		return (1);
	if (unlock_mutex(&philo->next_fork->fork) != 0)
		return (1);
	return (0);
}

int	check_death(t_ph *philo)
{
	long	current;

	current = _gettime();
	if (philo->data->n_simulation && philo->diner_counter >= philo->data->n_simulation)
		philo->full = true; 
	if (is_done(philo->data))//checking is philo alive;
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

void	*philo_cycle(void *tmp)
{
	t_ph	*philo;

	philo = (t_ph *) tmp;
	while (!is_simulation_start(philo->data))
		;
	philo->last_diner = _gettime();
	if (philo->data->n_philo == 1)
	{
		lock_mutex(&philo->main_fork->fork);
		print_status("has taken a fork", philo);
		_usleep(philo->data->t_die, philo->data, philo);
		print_death(philo, _gettime());
		unlock_mutex(&philo->main_fork->fork);
		return (NULL);
	}
	while (!check_death(philo))
	{
		if (philo->full)
			return (NULL);
		if (check_death(philo))
			return (NULL);
		if (philo->full)
			return (NULL);
		if (philo->id % 2)
			usleep(250);
		if (check_death(philo))
			return (NULL);
		if (eating(philo) != 0)
			return (NULL);
		if (check_death(philo))
			return (NULL);
		if (philos_life(philo) != 0)
			return (NULL);
	}
	return (NULL);
}

int	init_threads(t_sim *data)
{
	int	i;
	int	th;

	i = -1;
	while (++i < data->n_philo)
		data->philos[i].id = i + 1;
	i = 0;
	while (i < data->n_philo)
	{
		if (pthread_create(&data->philos[i].thread, NULL, philo_cycle, &data->philos[i]) != 0)
		{
			full_cleanup(data);
			return (print_error_return("Could't create a thread", 1));
		}
		i++;
	}
	data->started = true;
	data->simulation_starts = _gettime();
	i = 0;
	while (i < data->n_philo)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	return (0);
}

int	dinning(t_sim *data)
{
	if (init_threads(data))
		return (1); 
	return (0);
}
