/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_race_example.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:10:25 by aaferyad          #+#    #+#             */
/*   Updated: 2025/04/25 17:25:10 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdio.h>
# include <limits.h>
# include <pthread.h>

# define RED "\033[31m"
# define GREEN "\033[32m"
# define RESET "\033[0m"

#define T 21000

void	*test(void *data)
{
	pthread_t	id;
	int	*i = (int *) data;
	int	j = -1;

	id = pthread_self();
	printf("thread id :"GREEN"%ld"RESET" Start i : %d\n", id, *i);
	while (++j < T)
		*i = *i + 1;
	printf("thread id :"GREEN"%ld"RESET" End i : %d\n", id, *i);
	return (NULL);
}

int 	main(int ac, char **av)
{
	pthread_t	t1;
	pthread_t	t2;
	int	i;

	i = 0;
	pthread_create(&t1, NULL, test, &i);
	printf("main : created thread :"GREEN"%ld\n"RESET, t1);
	pthread_create(&t2, NULL, test, &i);
	printf("main : created thread :"GREEN"%ld\n"RESET, t2);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	if (i != T * 2)
		printf(RED"Wrong value %d"RESET, i);
	else
		printf(GREEN"Correct value %d"RESET, i);
	return (0);
}
/*
 * Created two threads t1 and t2
 * Printed it's id at first in the main thread (main thread is the inital thread every process has at least one thread which is the inital thread) 
 * Joined the two thread (We telling the inital thread to pause it self from excuting till the created theareds are done)
 * Each thread we created are taking the same variable address which is i the first thing thread do is printing when it started which value for ex : from 0 to T(21000)
 * Changing value of i (poiter to a variable in main)
 * 
 * If you run this simple program you will notice the values are changing, we expected [if thread (t1) started it will start from i = 0 to 21000 then thread (t2) from i = 21000 to 42000]
 * 	but we see opposite of this because of [data race]
 * Data race is when two threads are accessing the same memory at the same time. 
 * Let's say that we have two threads and we have a variable I = 10, the first thead is going to fetch from memory the value of I which is 10 and store it in a register
 * 	to manipulate it, then it adds 1. But before it can save the result to the memory address the second thread is also fetching from memory the value 10 and also adds 1
 * 	so we end up with incrementing the variable only once for each thread. That's why we are loosing counts and our final result is wrong.
 *
 * If we compile our program whit 'cc -fsanitize=thread -g data_race_example.c' it will throw an error/alert -> (“WARNING: ThreadSanitizer: data race”)
 * */
