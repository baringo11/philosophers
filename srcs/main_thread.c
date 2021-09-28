/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaringo <jbaringo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 13:22:11 by jbaringo          #+#    #+#             */
/*   Updated: 2021/09/28 19:00:03 by jbaringo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*main_routine(t_all *all)
{
	int			i;

	i = 0;
	while (1)
	{
		if (i == all->num_philos)
			i = 0;
		if (time_in_ms() > all->philo[i].last_time_eat + all->time_die)
		{
			pthread_mutex_lock(&all->print);
			print_status("died", i, all);
			all->is_alive = 0;
			pthread_mutex_unlock(&all->print);
			break;
		}
		i++;
	}
}

