/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hekrem <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 13:20:39 by hekrem            #+#    #+#             */
/*   Updated: 2023/03/03 13:20:41 by hekrem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sort_print(t_philo *pt_philo, char *str)
{
	pthread_mutex_lock(&pt_philo->list->mtx_print);
	if (!ft_death_check(pt_philo)
		&& pt_philo->eat_count != pt_philo->list->must_eat)
		printf("%lums %d %s", ft_clock() - pt_philo->list->begin_time,
			pt_philo->id + 1, str);
	pthread_mutex_unlock(&pt_philo->list->mtx_print);
}

void	ft_eating(t_philo *pt_philo)
{
	pthread_mutex_lock(pt_philo->left_fork);
	ft_sort_print(pt_philo, "has taken a fork\n");
	if (pt_philo->list->number_of_philosophers == 1)
	{
		ft_which_usleep(pt_philo, pt_philo->list->time_to_dead);
		pthread_mutex_unlock(pt_philo->left_fork);
		return ;
	}
	pthread_mutex_lock(pt_philo->right_fork);
	ft_sort_print(pt_philo, "has taken a fork\n");
	pthread_mutex_lock(&pt_philo->list->mtx_eat);
	pt_philo->last_time = ft_clock();
	ft_sort_print(pt_philo, "is eating\n");
	pt_philo->eat_count += 1;
	pthread_mutex_unlock(&pt_philo->list->mtx_eat);
	ft_which_usleep(pt_philo, pt_philo->list->time_to_eat);
	ft_sort_print(pt_philo, "is sleeping\n");
	pthread_mutex_unlock(pt_philo->left_fork);
	pthread_mutex_unlock(pt_philo->right_fork);
}

void	*ft_thread_begin(void *temp)
{
	t_philo	*pt_philo;

	pt_philo = temp;
	if (pt_philo->id % 2 == 1)
		usleep(1000);
	while (!ft_death_check(pt_philo))
	{
		ft_eating(pt_philo);
		ft_which_usleep(pt_philo, pt_philo->list->time_to_sleep);
		ft_sort_print(pt_philo, "is thinking\n");
	}
	return (NULL);
}

void	ft_thread_creat(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->list->number_of_philosophers)
		pthread_create(&philo[i].th_philo, NULL, ft_thread_begin, &philo[i]);
	while (42)
	{
		if (ft_death_write(philo) || ft_eat_write(philo))
			break ;
	}
}
