/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairou <mkhairou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 12:37:51 by mkhairou          #+#    #+#             */
/*   Updated: 2023/02/26 12:41:14 by mkhairou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    is_dead(t_philo *philo, t_main *args)
{
    int i;
    long time;

    i = -1;
    while (++i < args->number_of_philos)
    {
        time = (current_time() - philo[i].last_meal);
        if( time > args->time_to_die)
        {
            print_task(args,"died",i + 1);
            args->is_died = 1;
        }
    }
}

void    better_usleep(t_main *args, int bar)
{
    long i;

    i = current_time();
    while (!(args->is_died))
    {
        if(current_time() - i >= bar)
        {
            break;
        }
        usleep(50);
    }
}