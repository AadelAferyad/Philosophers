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

bool	is_done(t_sim *data)
{
	bool	is;

	lock_mutex(&data->end_simulation_mutex);
	is = data->end_simulation;
	unlock_mutex(&data->end_simulation_mutex);
	return (is);
}

bool	is_simulation_start(t_sim *data)
{
	bool	is;

	lock_mutex(&data->end_simulation_mutex);
	is = data->started;
	unlock_mutex(&data->end_simulation_mutex);
	return (is);
}
