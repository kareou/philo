/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairou <mkhairou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:20:21 by mkhairou          #+#    #+#             */
/*   Updated: 2023/02/26 13:28:40 by mkhairou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void print_task(t_main *args, char *a, int i)
{
    pthread_mutex_lock(&args->decalre);
    if (!args->is_died)
        printf("%ld\t%d\t%s\n", (current_time() - args->start_time), i, a);
    pthread_mutex_unlock(&args->decalre);
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

long current_time()
{
    struct timeval time;

    gettimeofday(&time, NULL);
    return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void *task(void *i)
{
    t_philo *philo = (t_philo *)i;
    t_main *args;
    args = philo->main;

    if (philo->id % 2 != 0)
        usleep(1500);
    print_task(args, "thinking", philo->id);
    while (!(args->is_died) && !(args->all_eat))
    {
        picking(philo);
        if (args->number_of_mealls > 0)
            check_all_eated(args);
        print_task(args, "sleeping", philo->id);
        better_usleep(args,args->time_to_sleep);
        print_task(args, "thinking", philo->id);
    }
    return (NULL);
}

int main(int ac, char **av)
{
    if (ac < 5)
        return (0);
    t_main *args;
    int i;

    check_positive(av);
    args = malloc(sizeof(t_main));
    init_main(args, av);
    start_thread(args);
    while (!(args->is_died) && !(args->all_eat))
        is_dead(args->philo, args);
    i = -1;
    while (++i < args->number_of_philos)
    {
        if (pthread_join(args->philo[i].number_of_philo, NULL))
            exit(1);
    }
    i = 0;
    while (i < args->number_of_philos)
    {
        pthread_mutex_destroy(&args->forks[i]);
        i++;
    }
    pthread_mutex_destroy(&args->decalre);
    free(args->philo);
    free(args->forks);
}