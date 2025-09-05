/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aflores- <aflores-@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-15 12:17:11 by aflores-          #+#    #+#             */
/*   Updated: 2025-05-15 12:17:11 by aflores-         ###   ########aflores-  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int check_death(t_rules *rules, int i, long now)
{
    pthread_mutex_lock(&rules->philos[i].meal_mutex);
    now = get_time();
    if ((now - rules->philos[i].last_meal) > rules->time_to_die)
    {
        rules->someone_died = 1;
        pthread_mutex_unlock(&rules->philos[i].meal_mutex);
        pthread_mutex_lock(&rules->print_mutex);
        printf("%ld %d died\n", now - rules->start_time, rules->philos[i].id);
        pthread_mutex_unlock(&rules->print_mutex);
        return (1);
    }
    pthread_mutex_unlock(&rules->philos[i].meal_mutex);
    return (0);
}

static int check_all_full(t_rules *rules)
{
    int result;

    result = 0;
    pthread_mutex_lock(&rules->full_mutex);
    if (rules->must_eat != -1 && rules->full_philos >= rules->nb_philo)
        result = 1;
    pthread_mutex_unlock(&rules->full_mutex);
    return (result);
}

void *death_monitor(void *arg)
{
    t_rules *rules;
    int     i;
    long    now;

    rules = (t_rules *)arg;
    now = 0;
    while (!rules->someone_died)
    {
        i = 0;
        while (i < rules->nb_philo)
        {
            if (check_death(rules, i, now))
                return (NULL);
            i++;
        }
        if (check_all_full(rules))
            return (NULL);
        usleep(1000);
    }
    return (NULL);
}
