#include "philo.h"

int	check_if_dead(t_philo *philo)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&philo->list->mtx_eat);
	while (++i < philo->list->number_of_philosophers)
	{
		if (ft_diff_time(philo[i].last_time) >= philo->list->time_to_dead)
		{
			ft_sort_print(&philo[i], "is dead\n");
			assign_dead_value(philo);
			pthread_mutex_unlock(&philo->list->mtx_eat);
			return (1);
		}
	}
	pthread_mutex_unlock(&philo->list->mtx_eat);
	return (0);
}

int	check_all_eat(t_philo *philo)
{
	int	i;

	if (philo->list->must_eat == -42)
		return (0);
	i = -1;
	pthread_mutex_lock(&philo->list->mtx_eat);
	while (++i < philo->list->number_of_philosophers)
	{
		if (philo[i].eat_count < philo->list->must_eat)
		{
			pthread_mutex_unlock(&philo->list->mtx_eat);
			return (0);
		}
	}
	pthread_mutex_unlock(&philo->list->mtx_eat);
	assign_dead_value(philo);
	return (1);
}

void	assign_dead_value(t_philo *philo)
{
	pthread_mutex_lock(&philo->list->mtx_death);
	philo->list->death_num = 1;
	pthread_mutex_unlock(&philo->list->mtx_death);
}