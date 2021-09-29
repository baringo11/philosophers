/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaringo <jbaringo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 13:22:11 by jbaringo          #+#    #+#             */
/*   Updated: 2021/09/29 11:39:08 by jbaringo         ###   ########.fr       */
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
			uint64_t time = time_in_ms();
		if (time > all->last_time_eat[i] + all->time_die ||
			all->cont_iterations == all->num_philos)
		{
			pthread_mutex_lock(&all->print);
			if (all->cont_iterations == all->num_philos)
				printf("**FINISH**\n");
			else
				printf("%lldms %d died\n", time_in_ms() - all->start_time, ++i);
			all->is_alive = 0;
			pthread_mutex_unlock(&all->print);
			break;
		}
		i++;
	}
	return (0);
}
