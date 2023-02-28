#include "philo.h"

int	ft_death_time_main(t_philo *pt_philo)
{
	pthread_mutex_lock(&pt_philo->list->mtx_eat);
	if (ft_diff_time(pt_philo->last_time) >= pt_philo->list->time_to_dead)
	{
		ft_sort_print(pt_philo, "died\n");
		pthread_mutex_lock(&pt_philo->list->mtx_death);
		pt_philo->list->death_num = 1;
		pthread_mutex_unlock(&pt_philo->list->mtx_death);
		pthread_mutex_unlock(&pt_philo->list->mtx_eat);
		return (0);
	}
	pthread_mutex_unlock(&pt_philo->list->mtx_eat);
	return (1);
}

int	ft_death_eat(t_philo *philo)
{
	int	i;
	int	flag;

	flag = 0;
	i = -1;
	pthread_mutex_lock(&philo->list->mtx_eat);
	if (philo->list->must_eat == -42)
	{
		pthread_mutex_unlock(&philo->list->mtx_eat);
		return (0);
	}
	while (++i < philo->list->number_of_philosophers)
	{
		if (philo[i].eat_count >= philo->list->must_eat)
			flag++;
	}
	if (flag == philo->list->number_of_philosophers)
	{
		philo->list->flag_eat = flag;
		pthread_mutex_unlock(&philo->list->mtx_eat);
		return (1);
	}
	pthread_mutex_unlock(&philo->list->mtx_eat);
	return (0);
}