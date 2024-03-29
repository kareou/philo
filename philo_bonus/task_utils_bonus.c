/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairou <mkhairou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:03:07 by mkhairou          #+#    #+#             */
/*   Updated: 2023/03/14 15:29:19 by mkhairou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*is_dead(void *phil)
{
	t_philo		*philo;
	t_main		*args;
	long long	time;

	philo = (t_philo *)phil;
	args = philo->main;
	while (1)
	{
		sem_wait(args->time);
		time = (current_time() - philo->last_meal);
		sem_post(args->time);
		if (time >= args->time_to_die)
		{
			sem_wait(args->declare);
			print_dead(args, "died", philo->id);
			args->is_died = 1;
			sem_post(args->eat);
			exit_proc(args);
		}
		if (args->number_of_mealls > 0 && args->eat_trgr == 0)
			check_mealls(args, philo);
	}
	return (NULL);
}

void	better_usleep(t_main *args, int bar)
{
	long	i;

	i = current_time();
	while (!(args->is_died))
	{
		if (current_time() - i >= bar)
			break ;
		usleep(50);
	}
}

void	*test(void *b)
{
	t_main	*args;
	int		i;

	i = -1;
	args = (t_main *)b;
	while (++i < args->number_of_philos)
		sem_wait(args->eat);
	i = -1;
	while (++i < args->number_of_philos)
		kill(args->id_tabel[i], 15);
	return (NULL);
}

void	wait_chillds(t_main *args)
{
	int			i;
	pthread_t	tmp;

	i = -1;
	if (args->number_of_mealls > 0)
		pthread_create(&tmp, NULL, test, args);
	waitpid(-1, 0, 0);
	if (args->number_of_mealls > 0)
		pthread_join(tmp, NULL);
	while (++i < args->number_of_philos)
		kill(args->id_tabel[i], 15);
	free(args->id_tabel);
}

void	init_semphor(t_main *args)
{
	sem_unlink("/forks");
	args->forks = sem_open("/forks", O_CREAT, 0777, args->number_of_philos);
	sem_unlink("/died");
	args->died = sem_open("/died", O_CREAT, 0777, 1);
	sem_unlink("/declare");
	args->declare = sem_open("/declare", O_CREAT, 0777, 1);
	sem_unlink("/meal");
	args->meal = sem_open("/meal", O_CREAT, 0777, 1);
	sem_unlink("/time");
	args->time = sem_open("/time", O_CREAT, 0777, 1);
	if (args->number_of_mealls > 0)
	{
		sem_unlink("/eat");
		args->eat = sem_open("/eat", O_CREAT, 0777, 0);
	}
}
