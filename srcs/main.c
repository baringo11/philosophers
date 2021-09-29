/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaringo <jbaringo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 11:32:31 by jbaringo          #+#    #+#             */
/*   Updated: 2021/09/29 19:35:32 by jbaringo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// valgrind --leak-check=full \
// 			--show-leak-kinds=all \
// 			--track-origins=yes \
// 			--verbose \
// 			--log-file=valgrind-out.txt \
// 			./philo

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

void	ret(void)
{
	system("leaks philo");
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
//	ret();
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
