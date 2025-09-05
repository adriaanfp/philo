/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aflores- <aflores-@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-15 12:21:51 by aflores-          #+#    #+#             */
/*   Updated: 2025-05-15 12:21:51 by aflores-         ###   ########aflores-  */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
