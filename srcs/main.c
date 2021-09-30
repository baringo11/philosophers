/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaringo <jbaringo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 11:32:31 by jbaringo          #+#    #+#             */
/*   Updated: 2021/09/30 11:13:15 by jbaringo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	initializase_var(t_all *all)
{
	all->num_philos = 0;
	all->flag_iterations = 0;
	all->cont_iterations = 0;
	all->is_alive = 1;
	pthread_mutex_init(&all->index_mutex, NULL);
	pthread_mutex_init(&all->print, NULL);
	pthread_mutex_init(&all->iterate_mutex, NULL);
}

int	main(int argc, char **argv)
{
	t_all	*all;

	all = malloc(sizeof (t_all));
	if (!all)
		return (str_error("error, malloc structure"));
	initializase_var(all);
	if (!check_arguments(argc, argv, all))
		return (-1);
	if (!threads(all))
		return (-1);
	clean(all);
	return (0);
}

void	clean(t_all *all)
{
	int	i;

	i = -1;
	while (++i < all->num_philos)
		pthread_mutex_destroy(&all->forks[i]);
	pthread_mutex_destroy(&all->print);
	pthread_mutex_destroy(&all->index_mutex);
	pthread_mutex_destroy(&all->iterate_mutex);
	free(all->last_time_eat);
	free(all->threads);
	free(all->forks);
	free(all);
}
