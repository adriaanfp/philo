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

typedef struct s_rules
{
    int nb_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int must_eat;
    long start_time;
    pthread_mutex_t *forks;
    pthread_mutex_t print_mutex;
}   t_rules;

typedef struct s_philo
{
    int id;
    int meals_eaten;
    long    last_meal;
    pthread_t thread_id;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *rigth_fork;
    t_rules *rules;
}   t_philo;



#endif
