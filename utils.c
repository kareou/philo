/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairou <mkhairou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 11:36:51 by mkhairou          #+#    #+#             */
/*   Updated: 2023/02/25 16:43:00 by mkhairou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void picking(t_philo *philo)
{
    t_main *args = philo->main;

    pthread_mutex_lock(&args->forks[philo->fork_left]);
    pthread_mutex_lock(&args->forks[philo->fork_right]);
    print_task(args, "picked fork", philo->id);
    // print_task(args, "picked fork", philo->id);
    print_task(args, "eating", philo->id);
    usleep(args->time_to_eat * 1000);
    philo->meal_eated++;
    philo->last_meal = current_time();
    pthread_mutex_unlock(&args->forks[philo->fork_left]);
    pthread_mutex_unlock(&args->forks[philo->fork_right]);
    // print_task(args, "puted fork", philo->id);
    print_task(args, "puted fork", philo->id);
}

int ft_atoi(const char *str)
{
    int i;
    int res;

    i = 0;
    res = 0;
    while (str && str[i] >= 48 && str[i] <= 57)
    {
        res = res * 10;
        res = res + str[i] - 48;
        i++;
    }
    return (res);
}

void    check_positive(char **a)
{
    int i;

    i = 1;
    while (a[i])
    {
        if(ft_atoi(a[i]) <= 0)
            exit(0);
        i++;
    }
}

void init_main(t_main *args, char **av)
{
    int i;
    
    args->philo = malloc(ft_atoi(av[1]) * sizeof(t_philo));
    args->forks = malloc(ft_atoi(av[1]) * sizeof(pthread_mutex_t));
    args->number_of_philos = ft_atoi(av[1]);
    args->time_to_die = ft_atoi(av[2]);
    args->time_to_eat = ft_atoi(av[3]);
    args->time_to_sleep = ft_atoi(av[4]);
    args->is_died = 0;
    args->all_eat = 0;
    args->start_time = current_time();
    pthread_mutex_init(&args->decalre, NULL);
    if (av[5] != 0)
        args->number_of_mealls = ft_atoi(av[5]);
    else
        args->number_of_mealls = -1;
    i = -1;
    while (++i < args->number_of_philos)
    {
        if (pthread_mutex_init(&args->forks[i], NULL))
            exit(1);
    }
}

void    start_thread(t_main *args)
{
    int i;
    
    i = -1;
    while (++i < args->number_of_philos)
    {
        args->philo[i].id = i + 1;
        args->philo[i].fork_left = i;
        args->philo[i].fork_right = (i + 1) % args->number_of_philos;
        args->philo[i].meal_eated = 0;
        args->philo[i].main = args;
        if (pthread_create(&args->philo[i].number_of_philo, NULL, &task, &args->philo[i]))
            exit(1);
        args->philo[i].last_meal = current_time();
    }
}
