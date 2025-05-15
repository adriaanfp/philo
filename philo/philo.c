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

void    parse_args(int ac, char **av, t_rules *rules)
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

int init_philo(t_rules *rules)
{
    int i;

    i = 0;
    while (i < rules->nb_philo)
    {
        if (pthread_mutex_init(&rules->forks[i], NULL) != 0)
        {
            printf("Error: mutex init failed for fork %d\n", i);
			return (0);
        }
        i++;
    }
    i = 0;
}

int main(int ac, char **av, t_rules *rules)
{

}
