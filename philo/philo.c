/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aflores- <aflores-@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-15 12:17:11 by aflores-          #+#    #+#             */
/*   Updated: 2025-05-15 12:17:11 by aflores-         ###   ########aflores-  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int    parse_args(int ac, char **av, t_rules *rules)
{
    if (ac != 5 && ac != 6)
    {
        printf("Error: invalid number of arguments\n");
        return 0;
    }
    if (!safe_atol(av[1], &rules->nb_philo)
        || !safe_atol(av[2], &rules->time_to_die)
        || !safe_atol(av[3], &rules->time_to_eat)
        || !safe_atol(av[4], &rules->time_to_sleep)
        || (ac == 6 && !safe_atol(av[5], &rules->must_eat)))
    {
        printf("Error: invalid or out-of-range argument(s)\n");
        return 0;
    }
    if (rules->nb_philo < 0 || rules->nb_philo > 200)
    {
        printf("Error: number of philosophers must be between 1 and 200\n");
        return 0;
    }
    if (ac == 5)
        rules->must_eat = -1;
    return 1;
}

static void setup_philo(t_rules *rules, int i)
{
    rules->philos[i].id = i + 1;
	rules->philos[i].meals_eaten = 0;
    rules->philos[i].has_finished = 0;
	rules->philos[i].last_meal = rules->start_time;
	rules->philos[i].rules = rules;
	rules->philos[i].left_fork = &rules->forks[i];
	if (i == rules->nb_philo - 1)
		rules->philos[i].right_fork = &rules->forks[0];
	else
		rules->philos[i].right_fork = &rules->forks[i + 1];
}

int init_philo(t_rules *rules)
{
    int i;

    rules->someone_died = 0;
    rules->full_philos = 0;
    pthread_mutex_init(&rules->full_mutex, NULL);
    rules->start_time = get_time();
    i = 0;
    while (i < rules->nb_philo)
    {
        if (pthread_mutex_init(&rules->forks[i], NULL) != 0)
            return (0);
        i++;
    }
    if (pthread_mutex_init(&rules->print_mutex, NULL) != 0)
        return (0);

    i = 0;
    while (i < rules->nb_philo)
    {
        setup_philo(rules, i);
        if (pthread_mutex_init(&rules->philos[i].meal_mutex, NULL) != 0)
            return (0);
        i++;
    }
    return 1;
}

static int	init_all(t_rules *rules)
{
	if (!init_memory(rules))
		return (0);
	if (!init_philo(rules))
	{
		free_memory(rules);
		return (0);
	}
	if (!start_threads(rules))
	{
		free_memory(rules);
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_rules		rules;
	pthread_t	death_thread;

	if (!parse_args(argc, argv, &rules))
		return (1);
	if (!init_all(&rules))
		return (1);
	if (pthread_create(&death_thread, NULL, death_monitor, &rules) != 0)
	{
		printf("Error creando hilo de monitor\n");
		free_memory(&rules);
		return (1);
	}
	pthread_join(death_thread, NULL);
	free_memory(&rules);
	return (0);
}