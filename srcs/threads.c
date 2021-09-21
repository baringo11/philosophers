/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaringo <jbaringo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 18:32:27 by jbaringo          #+#    #+#             */
/*   Updated: 2021/09/21 20:29:22 by jbaringo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int n = 0;

void	eat(t_all *all)
{
//	while (pthread_mutex_lock(&all->forks[0]) && pthread_mutex_lock(&all->forks[1]));
}

void	*prueba(t_all *all)
{
	struct timeval tv;
	time_t start_sec;
	suseconds_t start_usec;
	int i = -1;

	gettimeofday(&tv, NULL);
	start_sec = tv.tv_sec;
	start_usec = tv.tv_usec;
	printf("time: %ld : %ld\n", start_sec, start_usec);

	//eat(all);
	while (++i < 10000000)
	{
		pthread_mutex_lock(&all->forks[0]);
		n++;
		pthread_mutex_unlock(&all->forks[0]);
	}
	/*
	printf("mutex: %d\n", pthread_mutex_lock(&all->forks[0]));
	printf("mutex1: %d\n", pthread_mutex_lock(&all->forks[0]));
	printf("mutex2: %d\n", pthread_mutex_unlock(&all->forks[0]));

		pthread_mutex_unlock(&all->forks[0]);
*/
	gettimeofday(&tv, NULL);
	printf("final time: %ld : %ld\n", tv.tv_sec, tv.tv_usec);
}

int	threads(t_all *all)
{
	int	i;

	i = -1;
	while (++i < all->num_philos)
	{
		pthread_mutex_init(&all->forks[i], NULL);
		all->philo[i].is_alive = 1;
	}
	i = -1;
	while (++i < all->num_philos)
		if (pthread_create(&all->threads[i], NULL, (void *)&prueba, &all) != 0)
			return (str_error("Error making threads"));
	i = -1;
	while (++i < all->num_philos)
		if (pthread_join(all->threads[i], NULL) != 0)
			return (str_error("Error joining threads"));
	i = -1;
	while (++i < all->num_philos)
		pthread_mutex_destroy(&all->forks[i]);

		printf("n: %d\n", n);
	return (1);
}
