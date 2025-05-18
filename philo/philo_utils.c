/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aflores- <aflores-@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-15 12:21:51 by aflores-          #+#    #+#             */
/*   Updated: 2025-05-15 12:21:51 by aflores-         ###   ########aflores-  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(const char *str)
{
	long	i;
	long	sign;
	long	n;

	i = 0;
	sign = 1;
	n = 0;
	while (((str[i] >= 9 && str[i] <= 13) || str[i] == 32) && str[i])
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while ((str[i] >= '0' && str[i] <= '9') && str[i])
	{
		n = n * 10 + (str[i] - '0');
		i++;
	}
	return (n * sign);
}

int safe_atol(const char *s, int *out)
{
    long    value;

    if (!is_digit_str(s))
        return 0;
    value = ft_atol(s);
    if (value > INTMAX || value < 0)
        return 0;
    *out = (int)value;
    return 1;
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

int is_digit_str(const char *s)
{
    if(!s || *s == '\0')
        return 0;
    while (*s)
    {
        if (!ft_isdigit(*s))
            return 0;
        s++;
    }
    return 1;
}

int init_memory(t_rules *rules)
{
    rules->forks = malloc(sizeof(pthread_mutex_t) * rules->nb_philo);
    if (!rules->forks)
    {
        printf("Error allocating forks\n");
        return 0;
    }
    rules->philos = malloc(sizeof(t_philo) * rules->nb_philo);
    if (!rules->philos)
    {
        printf("Error allocating philosophers\n");
        free(rules->forks);
        return 0;
    }
    return 1;
}

void free_memory(t_rules *rules)
{
    int i;

    i = 0;
    while (i < rules->nb_philo)
    {
        pthread_mutex_destroy(&rules->forks[i]);
        pthread_mutex_destroy(&rules->philos[i].meal_mutex);
        i++;
    }
    pthread_mutex_destroy(&rules->print_mutex);
    pthread_mutex_destroy(&rules->full_mutex);
    free(rules->forks);
    rules->forks = NULL;
    free(rules->philos);
    rules->philos = NULL;
}

long	get_time(void)
{
	struct timeval	tv;
	long			time_in_ms;

	gettimeofday(&tv, NULL);
	time_in_ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time_in_ms);
}

void *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    while (!philo->rules->someone_died)
    {
        printf("Philosopher %d is thinking\n", philo->id);
        usleep(1000);
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
        printf("Philosopher %d is eating\n", philo->id);
        pthread_mutex_lock(&philo->meal_mutex);
        philo->last_meal = get_time();
        philo->meals_eaten++;
        if (!philo->has_finished && philo->rules->must_eat != -1 && philo->meals_eaten == philo->rules->must_eat)
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
        printf("Philosopher %d is sleepin\n", philo->id);
        usleep(philo->rules->time_to_sleep * 1000);
    }
    return NULL;
}

int start_threads(t_rules * rules)
{
    int i;

    i = 0;
    rules->start_time = get_time();
    while (i < rules->nb_philo)
    {
        if (pthread_create(&rules->philos[i].thread_id, NULL, routine, &rules->philos[i]) != 0)
        {
            printf("Error creating thread for philosopher %d\n", i + 1);
            return 0;
        }
        i++;
    }
    return 1;
}

void *death_monitor(void *arg)
{
    t_rules *rules = (t_rules *)arg;
    int i;
    long now;

    while (!rules->someone_died)
    {
        i = 0;
        while (i < rules->nb_philo)
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
                return NULL;
            }
            pthread_mutex_unlock(&rules->philos[i].meal_mutex);
            i++;
        }
        pthread_mutex_lock(&rules->full_mutex);
        if (rules->must_eat != -1 && rules->full_philos >= rules->nb_philo)
        {
            pthread_mutex_unlock(&rules->full_mutex);
            return NULL;
        }
        pthread_mutex_unlock(&rules->full_mutex);
        usleep(1000);
    }
    return NULL;
}
