/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaringo <jbaringo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 11:58:30 by jbaringo          #+#    #+#             */
/*   Updated: 2021/09/22 14:39:47 by jbaringo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct	s_philo
{
	int			is_alive;
	int			state[3];

}				t_philo;

typedef struct	s_all
{
	int			num_philos;
	int			index;
	int			time_die;
	int			time_eat;
	int			time_sleep;
	int			num_iterations[2];
	pthread_t	*threads;
	pthread_mutex_t *forks;
	time_t start_sec;
	suseconds_t start_usec;
	t_philo		*philo;

}				t_all;

int		threads(t_all *all);
int		str_error(char	*error);
int		ft_atoi(const char *str);
void	ft_putstr_fd(char *s, int fd);