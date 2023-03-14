/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colose_semaphores_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairou <mkhairou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:02:45 by mkhairou          #+#    #+#             */
/*   Updated: 2023/03/14 15:28:47 by mkhairou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	close_sema(t_main *args)
{
	sem_close(args->forks);
	sem_unlink("/forks");
	sem_close(args->died);
	sem_unlink("/died");
	if (args->number_of_mealls > 0)
	{
		sem_post(args->eat);
		sem_close(args->eat);
		sem_unlink("/eat");
	}
	sem_close(args->declare);
	sem_unlink("/declare");
	sem_close(args->meal);
	sem_unlink("/meal");
}

void	check_mealls(t_main *args, t_philo *philo)
{
	sem_wait(args->meal);
	if (philo->meal_eated >= args->number_of_mealls)
	{
		sem_post(args->eat);
		args->eat_trgr = 1;
	}
	sem_post(args->meal);
}

void	exit_proc(t_main *args)
{
	int	i;

	i = 0;
	if (args->number_of_mealls > 0)
	{
		while (i < args->number_of_philos)
		{
			sem_post(args->eat);
			i++;
		}
	}
	exit(1);
}
