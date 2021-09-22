/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaringo <jbaringo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 11:32:31 by jbaringo          #+#    #+#             */
/*   Updated: 2021/09/22 14:39:56 by jbaringo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_arguments(char **argv, t_all *all)
{
	all->num_philos = ft_atoi(argv[1]);
	all->time_die = ft_atoi(argv[2]) * 1000;
	all->time_eat = ft_atoi(argv[3]) * 1000;
	all->time_sleep = ft_atoi(argv[4]) * 1000;
	if (argv[5])
	{
		all->num_iterations[0] = 1;
		all->num_iterations[1] = ft_atoi(argv[5]);
	}
	if (all->num_philos < 0 || all->time_die <= 0 || all->time_eat <= 0 || \
		all->time_sleep <= 0 || all->num_iterations[1] <= 0)
		return (-1);
	all->threads = malloc(sizeof(pthread_t) * all->num_philos);
	all->forks = malloc(sizeof(pthread_mutex_t) * all->num_philos);
	all->philo = (t_philo *)malloc(sizeof(t_philo) * all->num_philos);
	if (!all->threads || !all->forks || !all->philo)
		return (0);
	
	return (1);
}

void	initializase_var(t_all *all)
{
	all->num_philos = 0;
	all->num_iterations[0] = 0;
	all->num_iterations[1] = 1;
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
