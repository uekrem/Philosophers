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