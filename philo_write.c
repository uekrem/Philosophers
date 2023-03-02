#include "philo.h"

int	ft_death_write(t_philo *philo)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&philo->list->mtx_eat);
	while (++i < philo->list->number_of_philosophers)
	{
		if (ft_diff_time(philo[i].last_time) >= philo->list->time_to_dead)
		{
			ft_death_change(philo);
			pthread_mutex_unlock(&philo->list->mtx_eat);
			printf("%lums %d %s", ft_clock() - philo->list->begin_time, philo[i].id + 1, "dead\n");
			return (1);
		}
	}
	pthread_mutex_unlock(&philo->list->mtx_eat);
	return (0);
}

int	ft_eat_write(t_philo *philo)
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
	ft_death_change(philo);
	return (1);
}

void	ft_death_change(t_philo *philo)
{
	pthread_mutex_lock(&philo->list->mtx_death);
	philo->list->death_num = 1;
	pthread_mutex_unlock(&philo->list->mtx_death);
}