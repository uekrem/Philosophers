#include "philo.h"

void	ft_which_usleep(t_philo *pt_philo, int which)
{
	unsigned long	counter_time;

	counter_time = ft_clock();
	while ((ft_clock() - counter_time) < which)
		usleep(100);
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
