/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairou <mkhairou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 14:46:20 by mkhairou          #+#    #+#             */
/*   Updated: 2023/03/02 12:24:22 by mkhairou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long current_time()
{
    struct timeval time;

    gettimeofday(&time, NULL);
    return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void print_task(t_main *args, char *a, int i)
{
    if (!args->is_died)
        printf("%ld\t%d\t%s\n", (current_time() - args->start_time), i, a);
}

void check_all_eated(t_main *args)
{
    int i;

    i = -1;
    while (++i < args->number_of_philos)
    {
        if (args->philo[i].meal_eated < args->number_of_mealls)
            return;
    }
    args->all_eat = 1;
}

void *task(t_philo *philo)
{
    t_main *args;
    args = philo->main;

    if (philo->id % 2 == 0)
        usleep(1500);
    print_task(args, "thinking", philo->id);
    while (!(args->is_died) && !(args->all_eat))
    {
        picking(philo);
        if (args->number_of_mealls > 0)
            check_all_eated(args);
        print_task(args, "sleeping", philo->id);
        better_usleep(args, args->time_to_sleep);
        print_task(args, "thinking", philo->id);
        is_dead(philo, args);
    }
    return (NULL);
}

void    start(char **av)
{
    t_main *args;
    // int i;
    
    args = malloc(sizeof(t_main));
    init_main(args,av);
    sem_unlink("/forks");
    args->forks = sem_open("/forks",O_CREAT, 0777, args->number_of_philos);
    start_thread(args);
    sem_close(args->forks);
    sem_unlink("/forks");
    free(args->philo);
}

int main(int ac, char **av)
{
    if (ac < 5)
        return (1);
    else
        start(av);
}