#include "philo.h"

void	ft_sort_print(t_philo *pt_philo, char *str)
{
	pthread_mutex_lock(&pt_philo->list->mtx_print);
	if (ft_death_checker(pt_philo))		
		printf("%lums %d %s", ft_clock() - pt_philo->list->begin_time, pt_philo->id + 1, str);
	pthread_mutex_unlock(&pt_philo->list->mtx_print);
}

void	ft_eating(t_philo *pt_philo)
{
	pthread_mutex_lock(pt_philo->left_fork);
	ft_sort_print(pt_philo, "has taken a fork\n");
	if (pt_philo->list->number_of_philosophers == 1)			
	{
		usleep(pt_philo->list->time_to_dead);
		pthread_mutex_unlock(pt_philo->left_fork);
		return ;
	}
	pthread_mutex_lock(pt_philo->right_fork);
	ft_sort_print(pt_philo, "has taken a fork\n");
	ft_sort_print(pt_philo, "is eating\n");
	pthread_mutex_lock(&pt_philo->list->mtx_eat);
	pt_philo->last_time = ft_clock();
	pt_philo->eat_count += 1;
	pthread_mutex_unlock(&pt_philo->list->mtx_eat);
	ft_which_usleep(pt_philo, pt_philo->list->time_to_eat);
	if (ft_death_eat_mutex_check(pt_philo))
		ft_sort_print(pt_philo, "is sleeping\n");
	pthread_mutex_unlock(pt_philo->left_fork);
	pthread_mutex_unlock(pt_philo->right_fork);
	ft_which_usleep(pt_philo, pt_philo->list->time_to_sleep);
}

void	*ft_thread_begin(void *temp)
{
	t_philo	*pt_philo;

	pt_philo = temp;
	if (pt_philo->id % 2 == 1)
		usleep(1000);
	while (ft_death_checker(pt_philo) && ft_death_eat_mutex_check(pt_philo))
	{
		ft_eating(pt_philo);
		if (pt_philo->list->number_of_philosophers == 1)
			break ;
		if (!ft_death_checker(pt_philo) || !ft_death_eat_mutex_check(pt_philo))
			break ;
		ft_sort_print(pt_philo, "is thinking\n");
	}
	return (NULL);
}

void	ft_thread_creat(t_philo *philo)
{
	int i;

	i = -1;
	while (++i < philo->list->number_of_philosophers)
		pthread_create(&philo[i].th_philo, NULL, ft_thread_begin, &philo[i]);
	while (42)
	{
		i = -1;
		while (++i < philo->list->number_of_philosophers)
		{
			if (ft_death_eat(philo))
				break ;
			if (ft_death_time_main(&philo[i]))
			{
				if (i == philo->list->number_of_philosophers - 1)
					i = -1;
				continue ;
			}
			break ;
		}
		break ;
	}
}