/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hekrem <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 13:21:05 by hekrem            #+#    #+#             */
/*   Updated: 2023/03/03 13:21:06 by hekrem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_death_check(t_philo *pt_philo)
{
	pthread_mutex_lock(&pt_philo->list->mtx_death);
	if (pt_philo->list->death_num == 1)
	{
		pthread_mutex_unlock(&pt_philo->list->mtx_death);
		return (1);
	}
	pthread_mutex_unlock(&pt_philo->list->mtx_death);
	return (0);
}
