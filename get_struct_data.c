/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_struct_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:23:00 by aaferyad          #+#    #+#             */
/*   Updated: 2025/07/30 18:06:25 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	*is_simulation_start(void)
{
	static int	start;
	static int	init_static;

	if (init_static == 0)
	{
		start = false;
		init_static = 1;
	}
	return (&start);
}

int	*get_time_to_sleep(void)
{
	static int	time_to_sleep;

	return (&time_to_sleep);
}

int	*get_time_to_eat(void)
{
	static int	time_to_eat;

	return (&time_to_eat);
}
