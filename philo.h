/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hekrem <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 13:20:28 by hekrem            #+#    #+#             */
/*   Updated: 2023/03/03 13:20:29 by hekrem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_list
{
	int				number_of_philosophers;
	int				time_to_dead;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	unsigned long	begin_time;
	int				death_num;
	pthread_mutex_t	mtx_print;
	pthread_mutex_t	mtx_eat;
	pthread_mutex_t	mtx_death;
	pthread_mutex_t	*fork;
}					t_list;

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	unsigned long	last_time;
	int				eat_count;
	pthread_t		th_philo;
	t_list			*list;
}					t_philo;

long				ft_atoi(char *str);
void				ft_thread_creat(t_philo *philo);
int					ft_death_eat(t_philo *philo);
unsigned long		ft_clock(void);
int					ft_diff_time(unsigned long last_time);
void				ft_which_usleep(t_philo *pt_philo, int which);
int					ft_eat_write(t_philo *philo);
void				ft_death_change(t_philo *philo);
int					ft_death_write(t_philo *philo);
int					ft_death_check(t_philo *pt_philo);
int					ft_int_rang(char **str, int argc);
int					ft_arg_letter(char **str, int argc);
int					ft_death_check(t_philo *pt_philo);
void				ft_sort_print(t_philo *pt_philo, char *str);

#endif
