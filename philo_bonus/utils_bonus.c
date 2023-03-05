/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairou <mkhairou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 11:31:38 by mkhairou          #+#    #+#             */
/*   Updated: 2023/03/05 15:36:35 by mkhairou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_main(t_main *args, char **av)
{
	args->philo = malloc(ft_atoi(av[1]) * sizeof(t_philo));
	args->number_of_philos = ft_atoi(av[1]);
	args->time_to_die = ft_atoi(av[2]);
	args->time_to_eat = ft_atoi(av[3]);
	args->time_to_sleep = ft_atoi(av[4]);
	args->is_died = 0;
	args->all_eat = 0;
	args->start_time = current_time();
	if (av[5] != 0)
		args->number_of_mealls = ft_atoi(av[5]);
	else
		args->number_of_mealls = -1;
}

void	start_thread(t_main *args)
{
	int		i;
	int		id;
	int		*id_tabel;

	id_tabel = malloc(sizeof(int) * args->number_of_philos);
	if (!id_tabel)
		exit(1);
	i = -1;
	while (++i < args->number_of_philos)
	{
		id = fork();
		if (id == 0)
		{
			args->philo[i].id = i + 1;
			args->philo[i].meal_eated = 0;
			args->philo[i].main = args;
			args->philo[i].last_meal = current_time();
			task(&args->philo[i]);
		}
		else if (id < 0)
			exit(1);
		else
			id_tabel[i] = id;
	}
	wait_chillds(args, id_tabel);
}

void	picking(t_philo *philo)
{
	t_main	*args;

	args = philo->main;
	sem_wait(args->forks);
	print_task(args, "has taken a fork", philo->id);
	if (args->number_of_philos == 1)
	{
		better_usleep(args, args->time_to_die);
		args->is_died = 1;
		return ;
	}
	sem_wait(args->forks);
	print_task(args, "has taken a fork", philo->id);
	print_task(args, "is eating", philo->id);
	philo->meal_eated++;
	philo->last_meal = current_time();
	better_usleep(args, args->time_to_eat);
	sem_post(args->forks);
	print_task(args, "puted forks", philo->id);
	sem_post(args->forks);
	print_task(args, "puted forks", philo->id);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	res = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str && str[i] >= 48 && str[i] <= 57)
	{
		res = res * 10;
		res = res + str[i] - 48;
		i++;
	}
	return (res * sign);
}

int	check_positive(char **a)
{
	int	i;

	i = 1;
	while (a[i])
	{
		if (ft_atoi(a[i]) <= 0)
			return (0);
		i++;
	}
	return (1);
}
