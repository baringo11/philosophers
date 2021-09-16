/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaringo <jbaringo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 11:32:31 by jbaringo          #+#    #+#             */
/*   Updated: 2021/09/16 12:49:09 by jbaringo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_arguments(char **argv, t_all *all)
{
	all->num_philo = ft_atoi(argv[1]);
	return (1);
}

void	initializase_var(t_all *all)
{
	all->num_philo = 0;
}

int	main(int argc, char **argv)
{
	t_all all;
	
	initializase_var(&all);
	check_arguments(argv, &all);

	return (0);
}