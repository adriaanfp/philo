/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aflores- <aflores-@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-15 12:03:18 by aflores-          #+#    #+#             */
/*   Updated: 2025-05-15 12:03:18 by aflores-         ###   ########aflores-  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define INTMIN -2147483648
# define INTMAX 2147483647

#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_rules t_rules;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal;
	pthread_t		thread_id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t meal_mutex;
	t_rules			*rules;
}	t_philo;

struct s_rules
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				someone_died;
	long			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	t_philo			*philos;
};

long	ft_atol(const char *str);
int	    ft_isdigit(int c);
int     is_digit_str(const char *s);
int     safe_atol(const char *s, int *out);
int     init_memory(t_rules *rules);
void    free_memory(t_rules *rules);
int     init_philo(t_rules *rules);
int     parse_args(int ac, char **av, t_rules *rules);
long	get_time(void);
int		start_threads(t_rules * rules);
void    *death_monitor(void *arg);

#endif
