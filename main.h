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

typedef struct s_philosopher	t_ph;

typedef struct s_philo_forks
{
	int		fork_id;
	pthread_mutex_t	fork;
} t_forks;

typedef struct s_parsed_data
{
	t_forks	*forks;
	t_ph	*philos;
	int		n_philo;
	int		t_die;
	int		t_eat;
	int		t_sleep;
	int		n_simulation;
	bool	started;
	time_t	simulation_starts;
	bool	end_simulation;
	pthread_mutex_t	end_simulation_mutex;
	pthread_mutex_t	print;
} t_sim;

struct	s_philosopher
{
	int			id;
	pthread_t			thread;
	unsigned int			diner_counter;
	bool		full;
	time_t		last_diner;
	t_forks		*main_fork;
	t_forks		*next_fork;
	t_sim		*data;
};

int		init(t_sim *data);
int		parser(t_sim *info, char **av);
void	print_error(char *msg);
void	*allocation(unsigned int bytes);
void	cleanup(t_sim *data);
bool	is_simulation_start(t_sim *data);
int		*get_time_to_sleep(void);
int		*get_time_to_eat(void);
int		print_error_return(char *error, int return_code);
int		dinning(t_sim *data);
int		full_cleanup(t_sim *data);
int		_usleep(time_t usec, t_sim *data, t_ph *philo);
int		print_death(t_ph *philo, long current);
time_t	_gettime(void);
int		check_death(t_ph *philo);
int		destroy_mutex(t_sim *data);
int		check_death(t_ph *philo);
bool	is_done(t_sim *data);
int		lock_mutex(pthread_mutex_t *lock);
int		unlock_mutex(pthread_mutex_t *lock);
#endif
