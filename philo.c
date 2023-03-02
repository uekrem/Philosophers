#include "philo.h"

void	ft_fork_assign(t_philo *philo, t_list *list)
{
	int	i;

	i = -1;
	list->fork = malloc(sizeof(pthread_mutex_t) * list->number_of_philosophers);
	while (++i < list->number_of_philosophers)
		pthread_mutex_init(&list->fork[i], NULL);
	i = -1;
	while (++i < list->number_of_philosophers)
	{
		philo[i].right_fork = &list->fork[i];
		if (i == 0)
			philo[i].left_fork = &list->fork[list->number_of_philosophers - 1];
		else
			philo[i].left_fork = &list->fork[i - 1];
	}
	pthread_mutex_init(&list->mtx_print, NULL);
	pthread_mutex_init(&list->mtx_eat, NULL);
	pthread_mutex_init(&list->mtx_death, NULL);
}

t_philo	*ft_philo_assign(t_list *list)
{
	int		i;
	t_philo	*philo;

	i = -1;
	philo = malloc(sizeof(t_philo) * list->number_of_philosophers);
	while (++i < list->number_of_philosophers)
	{
		philo[i].id = i;
		philo[i].eat_count = 0;
		philo[i].list = list;
		philo[i].last_time = list->begin_time;
	}
	return (philo);
}

t_list	*ft_check_argv(char **str, int argc)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	list->number_of_philosophers = ft_atoi(str[1]);
	list->time_to_dead = ft_atoi(str[2]);
	list->time_to_eat = ft_atoi(str[3]);
	list->time_to_sleep = ft_atoi(str[4]);
	if (argc == 6)
		list->must_eat = ft_atoi(str[5]);
	else
		list->must_eat = -42;
	list->death_num = 0;
	return (list);
}

int	main(int argc, char **argv)
{
	t_list	*list;
	t_philo	*philo;
	int		i;

	i = -1;
	if (argc > 1)
		if (ft_atoi(argv[1]) == 0) 
			return (0);
	if (ft_arg_letter(argv, argc))
		return (0);
	if (ft_int_rang(argv, argc))
		return (0);
	if (argc == 5 || argc == 6)
	{
		list = ft_check_argv(argv, argc);
		list->begin_time = ft_clock();
		philo = ft_philo_assign(list);
		ft_fork_assign(philo, list);
		ft_thread_creat(philo);
		while (++i < list->number_of_philosophers)
			pthread_join(philo[i].th_philo, NULL);
	}
}
