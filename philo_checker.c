#include "philo.h"

void	ft_which_usleep(t_philo *pt_philo, int which)
{
	unsigned long	counter_time;

	counter_time = ft_clock();
	while ((ft_clock() - counter_time) < which)
		usleep(100);
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

unsigned long	ft_clock(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((unsigned long)((tv.tv_sec * 1000) + (tv.tv_usec / 1000)));
}

int	ft_diff_time(unsigned long last_time)
{
	return (ft_clock() - last_time);
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
