/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairou <mkhairou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 12:37:51 by mkhairou          #+#    #+#             */
/*   Updated: 2023/02/25 16:34:54 by mkhairou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    is_dead(t_philo *philo, t_main *args)
{
    int i;

    i = -1;
    while (++i < args->number_of_philos)
    {
        if((current_time() - philo[i].last_meal) > args->time_to_die)
        {
            print_task(args,"died",i + 1);
            args->is_died = 1;
        }
    }
}

