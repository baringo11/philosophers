/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaringo <jbaringo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 18:32:27 by jbaringo          #+#    #+#             */
/*   Updated: 2021/09/23 15:45:01 by jbaringo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

uint64_t	time_in_ms()
{
	struct timeval	tv;
	uint64_t		time;
	
	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}

void	micro_sleep(int time_to_sleep)
{
	uint64_t		time;

	time = time_in_ms();
	while (time_in_ms() > (time + time_to_sleep))
		usleep(100);
}

void	print_status(char *status, int index, suseconds_t time, t_all *all)
{
	if (all->is_alive)
		printf("%dms %d %s\n", time, index, status);
}

int	check_if_dead(int index, uint64_t time, t_all *all)
{
	if (time_in_ms() - all->start_time - time >= all->time_die)
	{
		print_status("died", index, time, all);
		all->is_alive = 0;
		return (1);
	}
	return (0);
}

suseconds_t	eat(int index, uint64_t actual_time, t_all *all)
{
	uint64_t	time;
	
	pthread_mutex_lock(&all->forks[0]);
	pthread_mutex_lock(&all->forks[1]);
	//time = actual_time;
	time = time_in_ms() - all->start_time + actual_time;

	print_status("has taken a fork", index, time, all);
//printf("********** time: %llu\n", time);
		if (check_if_dead(index, time, all))
			return (0);
		print_status("is eating", index, time, all);
		all->philo[index].time_before_eat = time;
	usleep(all->time_eat);
	pthread_mutex_unlock(&all->forks[0]);
	pthread_mutex_unlock(&all->forks[1]);
	time += time_in_ms() - all->start_time - time;
	print_status("is sleeping", index, time, all);
	//printf("*******time[%d]: %ld : %ld\n", index, tv.tv_sec, tv.tv_usec);
	usleep(all->time_sleep);
	time += time_in_ms() - all->start_time - time;
	print_status("is thinking", index, time, all);	
	return (time);
}

void	*prueba(t_all *all)
{
	uint64_t	actual_time;
	int			index;
	int			i = 1;

	pthread_mutex_lock(&all->index_mutex);
	index = all->index;
	all->index++;
	pthread_mutex_unlock(&all->index_mutex);

	actual_time = time_in_ms() - all->start_time;
//	printf("time[%d]: %llums\n", index, actual_time);
	while (all->philo[index].num_iterations > 0)
	{
		actual_time += eat(index, actual_time, all);
		if (all->flag_iterations)
			all->philo[index].num_iterations--;
		i++;
	}
	//gettimeofday(&tv, NULL);
	//printf("final time[%d]: %ld : %d\n", index, tv.tv_sec, tv.tv_usec);
	return (0);
}

int	threads(t_all *all)
{
	struct timeval tv;
	int				i;

	pthread_mutex_init(&all->index_mutex, NULL);
	i = -1;
	while (++i < all->num_philos)
	{
		pthread_mutex_init(&all->forks[i], NULL);
		all->philo[i].is_alive = 1;
	}
	all->index = 0;
	all->start_time = time_in_ms();
	i = -1;
	while (++i < all->num_philos)
		if (pthread_create(&all->threads[i], NULL, (void *)&prueba, all) != 0)
			return (str_error("Error making threads"));
	i = -1;
	while (++i < all->num_philos)
		if (pthread_join(all->threads[i], NULL) != 0)
			return (str_error("Error joining threads"));
	i = -1;
	while (++i < all->num_philos)
		pthread_mutex_destroy(&all->forks[i]);

	return (1);
}
