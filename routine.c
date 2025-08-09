/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 14:50:47 by aaferyad          #+#    #+#             */
/*   Updated: 2025/08/09 16:03:44 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	eating_helper(t_ph *philo)
{
	if (check_death(philo))
		return (1);
	if (philo->full)
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
	return (0);
}

int	eating(t_ph *philo)
{
	if (eating_helper(philo))
		return (1);
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

void	single_philo(t_ph *philo)
{
	lock_mutex(&philo->main_fork->fork);
	print_status("has taken a fork", philo);
	_usleep(philo->data->t_die, philo->data, philo);
	print_death(philo, _gettime());
	unlock_mutex(&philo->main_fork->fork);
}

int	cheker(t_ph *philo)
{
	if (philo->full)
		return (1);
	if (check_death(philo))
		return (1);
	if (philo->full)
		return (1);
	if (philo->id % 2)
		usleep(250);
	if (check_death(philo))
		return (1);
	if (eating(philo) != 0)
		return (1);
	if (check_death(philo))
		return (1);
	if (philos_life(philo) != 0)
		return (1);
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
		return (single_philo(philo), NULL);
	while (!check_death(philo))
	{
		if (cheker(philo))
			return (NULL);
	}
	return (NULL);
}
