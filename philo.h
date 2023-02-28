#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_list
{
    int             number_of_philosophers;
    int             time_to_dead;
    int             time_to_eat;
    int             time_to_sleep;
    int             must_eat;
    unsigned long   begin_time;
    int             death_num;
    int             flag_eat;
    pthread_mutex_t mtx_print;
    pthread_mutex_t mtx_eat;
    pthread_mutex_t mtx_death;
    pthread_mutex_t *fork;
}   t_list;

typedef struct s_philo
{
    int             id;
    pthread_mutex_t *right_fork;
    pthread_mutex_t *left_fork;  
    unsigned long   last_time;      
    int             eat_count;
    pthread_t       th_philo;
    t_list          *list;
}   t_philo;

int             ft_atoi(const char *nptr);
void            ft_thread_creat(t_philo *philo);
int             ft_death_eat(t_philo *philo);
unsigned long   ft_clock();
int             ft_diff_time(unsigned long last_time);
int	            ft_death_checker(t_philo *pt_philo);
void	        ft_which_usleep(t_philo *pt_philo, int which);
void            ft_sort_print(t_philo *pt_philo, char *str);
int	            ft_death_time_main(t_philo *pt_philo);
int	            ft_death_eat_mutex_check(t_philo *pt_philo);

#endif