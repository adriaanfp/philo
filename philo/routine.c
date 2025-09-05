/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aflores- <aflores-@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-15 12:17:11 by aflores-          #+#    #+#             */
/*   Updated: 2025-05-15 12:17:11 by aflores-         ###   ########aflores-  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void philo_take_forks(t_philo *philo)
{
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(philo->right_fork);
        pthread_mutex_lock(philo->left_fork);
    }
    else
    {
        pthread_mutex_lock(philo->left_fork);
        pthread_mutex_lock(philo->right_fork);
    }
}

static void philo_eat(t_philo *philo)
{
    printf("Philosopher %d is eating\n", philo->id);
    pthread_mutex_lock(&philo->meal_mutex);
    philo->last_meal = get_time();
    philo->meals_eaten++;
    if (!philo->has_finished && philo->rules->must_eat != -1
        && philo->meals_eaten == philo->rules->must_eat)
    {
        philo->has_finished = 1;
        pthread_mutex_lock(&philo->rules->full_mutex);
        philo->rules->full_philos++;
        pthread_mutex_unlock(&philo->rules->full_mutex);
    }
    pthread_mutex_unlock(&philo->meal_mutex);
    usleep(philo->rules->time_to_eat * 1000);
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}

static void philo_sleep(t_philo *philo)
{
    printf("Philosopher %d is sleeping\n", philo->id);
    usleep(philo->rules->time_to_sleep * 1000);
}

void *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    while (!philo->rules->someone_died)
    {
        printf("Philosopher %d is thinking\n", philo->id);
        usleep(1000);
        philo_take_forks(philo);
        philo_eat(philo);
        philo_sleep(philo);
    }
    return (NULL);
}
