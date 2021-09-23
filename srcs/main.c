/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaringo <jbaringo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 11:32:31 by jbaringo          #+#    #+#             */
/*   Updated: 2021/09/23 15:31:44 by jbaringo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_arguments(char **argv, t_all *all)
{
	int	i;

	all->num_philos = ft_atoi(argv[1]);
	all->time_die = ft_atoi(argv[2]) * 1000;
	all->time_eat = ft_atoi(argv[3]) * 1000;
	all->time_sleep = ft_atoi(argv[4]) * 1000;
	if (all->num_philos < 0 || all->time_die <= 0 || all->time_eat <= 0 || all->time_sleep <= 0)
		return (0);
	all->threads = malloc(sizeof(pthread_t) * all->num_philos);
	all->forks = malloc(sizeof(pthread_mutex_t) * all->num_philos);
	all->philo = (t_philo *)malloc(sizeof(t_philo) * all->num_philos);
	if (!all->threads || !all->forks || !all->philo)
		return (0);
	i = -1;
	if (argv[5])
	{
		all->flag_iterations = 1;
		while (++i < all->num_philos)
			all->philo[i].num_iterations = ft_atoi(argv[5]);
	}
	else
	{
		while (++i < all->num_philos)
			all->philo[i].num_iterations = 1;
	}
	return (1);
}

void	initializase_var(t_all *all)
{
	all->num_philos = 0;
	all->flag_iterations = 0;
	all->is_alive = 1;
}

int	main(int argc, char **argv)
{
	t_all *all;

	all = malloc(sizeof (t_all));
	if (!all)
		return (str_error("error, malloc structure"));
	initializase_var(all);
	if (!check_arguments(argv, all))
		return (-1);
	if (!threads(all))
		return (-1);
	return (0);
}
