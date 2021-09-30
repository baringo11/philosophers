/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaringo <jbaringo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 18:59:38 by jbaringo          #+#    #+#             */
/*   Updated: 2021/09/30 11:34:29 by jbaringo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_isdigit(int c)
{
	if (c > 47 && c < 58)
		return (1);
	return (0);
}

int	correct_argument(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (0);
		}
	}
	return (1);
}

int	check_arguments(int argc, char **argv, t_all *all)
{
	if (argc != 5 && argc != 6)
		return (str_error("error, wrong number of arguments"));
	if (!correct_argument(argv))
		return (str_error("error, only positive number arguments"));
	all->num_philos = ft_atoi(argv[1]);
	all->time_die = ft_atoi(argv[2]);
	all->time_eat = ft_atoi(argv[3]);
	all->time_sleep = ft_atoi(argv[4]);
	if (all->num_philos <= 0 || all->time_die <= 0 || \
		all->time_eat <= 0 || all->time_sleep <= 0)
		return (str_error("error, wrong number"));
	all->threads = malloc(sizeof(pthread_t) * all->num_philos);
	all->forks = malloc(sizeof(pthread_mutex_t) * all->num_philos);
	all->last_time_eat = malloc(sizeof(uint64_t) * all->num_philos);
	if (!all->threads || !all->forks || !all->last_time_eat)
		return (str_error("error, malloc structure"));
	if (argv[5])
	{
		all->flag_iterations = ft_atoi(argv[5]);
		if (all->flag_iterations == 0 || all->flag_iterations == -1)
			return (str_error("error, wrong number"));
	}
	return (1);
}
