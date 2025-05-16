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

void    free_memory(t_rules *rules)
{
    int i;

    i = 0;
    while (i < rules->nb_philo)
    {
        pthread_mutex_destroy(&rules->forks[i]);
        i++;
    }
    pthread_mutex_destroy(&rules->print_mutex);
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

void    *routine(void *arg)
{
    t_philo *philo = (void *)arg;

    printf("Philosopher %d is alive!\n", philo->id);
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