/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:49:08 by aaferyad          #+#    #+#             */
/*   Updated: 2025/08/07 15:42:43 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdio.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>

# define RED "\033[31m"
# define GREEN "\033[32m"
# define RESET "\033[0m"

typedef struct philosopher t_ph;

typedef struct	philo_forks
{
	int	fork_id;
	pthread_mutex_t	fork;
} t_forks;

typedef struct	parsed_data
{
	t_forks	*forks;
	t_ph	*philos;
	unsigned int	n_philo;
	unsigned int	t_die;
	unsigned int	t_eat;
	unsigned int	t_sleep;
	int	n_simulation;
	time_t	simulation_starts;
	bool	end_simulation;
	pthread_mutex_t	end_simulation_mutex;
	pthread_mutex_t	print;
} t_sim;

struct	philosopher
{
	int	id;
	pthread_t	thread;
	unsigned int	diner_counter;
	bool	full;
	unsigned int	last_diner;
	t_forks	*main_fork;
	t_forks	*next_fork;
	t_sim	*data;
};

int	init(t_sim *data);
int	parser(t_sim *info, char **av);
void	print_error(char *msg);
void	*allocation(unsigned int bytes);
void	cleanup(t_sim *data);
int	*is_simulation_start(void);
int	*get_time_to_sleep(void);
int	*get_time_to_eat(void);
int	print_error_exit(char *error, int exit_code);
int	dinning(t_sim *data);
int	full_cleanup(t_sim *data);
int	_usleep(long usec);
long	_gettime(void);

#endif
