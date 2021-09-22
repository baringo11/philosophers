/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaringo <jbaringo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 18:32:27 by jbaringo          #+#    #+#             */
/*   Updated: 2021/09/23 00:32:14 by jbaringo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int n = 0;

suseconds_t	eat(int index, time_t last_sec, suseconds_t last_usec, suseconds_t actual_usec, t_all *all)
{
	struct timeval tv;
	time_t actual_sec;
	//suseconds_t actual_usec;

	pthread_mutex_lock(&all->forks[0]);
	pthread_mutex_lock(&all->forks[1]);
		gettimeofday(&tv, NULL);
		actual_sec = tv.tv_sec - last_sec;
		if (actual_sec == 0)
			actual_usec += tv.tv_usec - last_usec;
		else
			actual_usec += tv.tv_usec + (1000000 - last_usec);
		last_sec = tv.tv_sec;
		last_usec = tv.tv_usec;
		printf("%ldms %d has taken a fork\n", actual_usec / 1000, index);
		printf("%ldms %d is eating\n", actual_usec / 1000, index);
	usleep(all->time_eat);
	pthread_mutex_unlock(&all->forks[0]);
	pthread_mutex_unlock(&all->forks[1]);
	gettimeofday(&tv, NULL);
	actual_sec = tv.tv_sec - last_sec;
	if (actual_sec == 0)
		actual_usec += tv.tv_usec - last_usec;
	else
		actual_usec += tv.tv_usec + (1000000 - last_usec);
	last_sec = tv.tv_sec;
	last_usec = tv.tv_usec;
	printf("%ldms %d is sleeping\n", actual_usec / 1000, index);
	//printf("*******time[%d]: %ld : %ld\n", index, tv.tv_sec, tv.tv_usec);
	usleep(all->time_sleep);
	gettimeofday(&tv, NULL);
//	printf("-------time[%d]: %ld : %ld\n", index, tv.tv_sec, tv.tv_usec);
	actual_sec = tv.tv_sec - last_sec;
	if (actual_sec == 0)
		actual_usec += tv.tv_usec - last_usec;
	else
		actual_usec += tv.tv_usec + (1000000 - last_usec);
	
	printf("%ldms %d is thinking\n", actual_usec / 1000, index);
	return (actual_usec);
}

void	*prueba(t_all *all)
{
	int index = all->index;
	all->index++;
	struct timeval tv;
	int i = 1;

	gettimeofday(&tv, NULL);
	time_t start_sec = tv.tv_sec - all->start_sec;
	suseconds_t start_usec = tv.tv_usec - all->start_usec;
	suseconds_t actual_usec = 0;
	printf("time[%d]: %ld : %06ld\n", index, start_sec, start_usec);
 
	while (all->num_iterations[1] > 0)
	{
		gettimeofday(&tv, NULL);
		if (actual_usec >= (all->time_die * i))
		{
			printf("i: %d\n", i);
			printf("%ldms %d died\n", actual_usec / 1000, index);
			return (NULL);
		}
		actual_usec = eat(index, tv.tv_sec, tv.tv_usec, actual_usec, all);
		if (all->num_iterations[0])
			all->num_iterations[1]--;
		i++;
	}
	gettimeofday(&tv, NULL);
		printf("final time[%d]: %ld : %ld\n", index, tv.tv_sec, tv.tv_usec);
//	free(all->index);
//	return (all);
}

int	threads(t_all *all)
{
	struct timeval tv;
	int				i;
	//int	*index;

	i = -1;
	while (++i < all->num_philos)
	{
		pthread_mutex_init(&all->forks[i], NULL);
		all->philo[i].is_alive = 1;
	}
	i = -1;
	all->index = 0;
	gettimeofday(&tv, NULL);
	all->start_sec = tv.tv_sec;
	all->start_usec = tv.tv_usec;
	while (++i < all->num_philos)
	{
		//int *index = malloc(sizeof(int));
		//*index = i;	
		if (pthread_create(&all->threads[i], NULL, (void *)&prueba, all) != 0)
			return (str_error("Error making threads"));
	}
	i = -1;
	while (++i < all->num_philos)
		if (pthread_join(all->threads[i], NULL) != 0)
			return (str_error("Error joining threads"));
	i = -1;
	while (++i < all->num_philos)
		pthread_mutex_destroy(&all->forks[i]);

	return (1);
}
