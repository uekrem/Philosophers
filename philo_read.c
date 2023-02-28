#include "philo.h"

int	ft_death_eat_mutex_check(t_philo *pt_philo)
{
	pthread_mutex_lock(&pt_philo->list->mtx_eat);
	if (pt_philo->list->flag_eat == pt_philo->list->number_of_philosophers)
	{
		pthread_mutex_unlock(&pt_philo->list->mtx_eat);
		return (0);
	}
	pthread_mutex_unlock(&pt_philo->list->mtx_eat);
	return (1);
}

int	ft_death_checker(t_philo *pt_philo)
{
	pthread_mutex_lock(&pt_philo->list->mtx_death);
	if (pt_philo->list->death_num == 1)
	{
		pthread_mutex_unlock(&pt_philo->list->mtx_death);
		return (0);
	}
	pthread_mutex_unlock(&pt_philo->list->mtx_death);
	return (1);
}