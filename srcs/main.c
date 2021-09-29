/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaringo <jbaringo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 11:32:31 by jbaringo          #+#    #+#             */
/*   Updated: 2021/09/29 11:40:26 by jbaringo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// valgrind --leak-check=full \
// 			--show-leak-kinds=all \
// 			--track-origins=yes \
// 			--verbose \
// 			--log-file=valgrind-out.txt \
// 			./philo

int	check_arguments(char **argv, t_all *all)
{
	int	i;

	all->num_philos = ft_atoi(argv[1]);
	all->time_die = ft_atoi(argv[2]);
	all->time_eat = ft_atoi(argv[3]);
	all->time_sleep = ft_atoi(argv[4]);
	if (all->num_philos < 0 || all->time_die <= 0 || all->time_eat <= 0 || all->time_sleep <= 0)
		return (0);
	all->threads = malloc(sizeof(pthread_t) * all->num_philos);
	all->forks = malloc(sizeof(pthread_mutex_t) * all->num_philos);
	all->last_time_eat = malloc(sizeof(uint64_t) * all->num_philos);
	if (!all->threads || !all->forks || !all->last_time_eat)
		return (0);
	i = -1;
	if (argv[5])
		all->flag_iterations = ft_atoi(argv[5]);
	return (1);
}

void	initializase_var(t_all *all)
{
	all->num_philos = 0;
	all->flag_iterations = 0;
	all->cont_iterations = 0;
	all->is_alive = 1;
}

void	ret()
{
	system("leaks philo");
}

int	main(int argc, char **argv)
{
	t_all *all;
argc = 1;
	all = malloc(sizeof (t_all));
	if (!all)
		return (str_error("error, malloc structure"));
	initializase_var(all);
	if (!check_arguments(argv, all))
		return (-1);
	if (!threads(all))
		return (-1);
	clean(all);
//	ret();
	return (0);
}

void	clean(t_all *all)
{
	free(all->last_time_eat);
	free(all->threads);
	free(all->forks);
	free(all);
}
