/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaringo <jbaringo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 18:32:27 by jbaringo          #+#    #+#             */
/*   Updated: 2021/09/29 19:35:07 by jbaringo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	micro_sleep(int time_to_sleep)
{
	__uint64_t		time;

	time = time_in_ms();
	while (time_in_ms() < (time + time_to_sleep))
		usleep(100);
}

void	print_status(char *status, int index, t_all *all)
{
	__uint64_t		time;

	time = time_in_ms() - all->start_time;
	pthread_mutex_lock(&all->print);
	if (all->is_alive)
		printf("%ldms %d %s\n", time, ++index, status);
	pthread_mutex_unlock(&all->print);
}

void	eat(int index, int next, int i, t_all *all)
{
	pthread_mutex_lock(&all->forks[index]);
	print_status("has taken a fork", index, all);
	if (all->num_philos == 1)
		return (micro_sleep(all->time_die * 2));
	pthread_mutex_lock(&all->forks[next]);
	print_status("has taken a fork", index, all);
	all->last_time_eat[index] = time_in_ms();
	print_status("is eating", index, all);
	micro_sleep(all->time_eat);
	pthread_mutex_unlock(&all->forks[index]);
	pthread_mutex_unlock(&all->forks[next]);
	print_status("is sleeping", index, all);
	micro_sleep(all->time_sleep);
	print_status("is thinking", index, all);
	if (all->flag_iterations && i == all->flag_iterations)
	{
		pthread_mutex_lock(&all->iterate_mutex);
		all->cont_iterations++;
		pthread_mutex_unlock(&all->iterate_mutex);
	}
}

void	*philos(t_all *all)
{
	int			index;
	int			next;
	int			i;

	pthread_mutex_lock(&all->index_mutex);
	index = all->index;
	all->index++;
	next = all->index;
	if (all->index >= all->num_philos)
		next = 0;
	pthread_mutex_unlock(&all->index_mutex);
	if (index % 2 != 0)
		micro_sleep(all->time_eat);
	i = 1;
	while (all->is_alive)
	{
		eat(index, next, i, all);
		i++;
	}
	return (0);
}

int	threads(t_all *all)
{
	int				i;
	pthread_t		main_thread;

	all->start_time = time_in_ms();
	while (++i < all->num_philos)
	{
		pthread_mutex_init(&all->forks[i], NULL);
		all->last_time_eat[i] = all->start_time;
	}
	all->index = 0;
	if (pthread_create(&main_thread, NULL, (void *)&main_routine, all) != 0)
		return (str_error("Error making threads"));
	i = -1;
	while (++i < all->num_philos)
		if (pthread_create(&all->threads[i], NULL, (void *)&philos, all) != 0)
			return (str_error("Error making threads"));
	if (pthread_join(main_thread, NULL) != 0)
		return (str_error("Error joining threads"));
	i = -1;
	while (++i < all->num_philos)
		if (pthread_join(all->threads[i], NULL) != 0)
			return (str_error("Error joining threads"));
	return (1);
}
