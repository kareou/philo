/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairou <mkhairou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 11:39:10 by mkhairou          #+#    #+#             */
/*   Updated: 2023/03/14 13:34:32 by mkhairou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	alloc_argument(t_main *args, char **av)
{
	args->philo = malloc(ft_atoi(av[1]) * sizeof(t_philo));
	if (!args->philo)
		return (0);
	args->forks = malloc(ft_atoi(av[1]) * sizeof(pthread_mutex_t));
	if (!args->forks)
		return (0);
	args->time = malloc(ft_atoi(av[1]) * sizeof(pthread_mutex_t));
	if (!args->time)
		return (0);
	args->eating = malloc(ft_atoi(av[1]) * sizeof(pthread_mutex_t));
	if (!args->eating)
		return (0);
	return (1);
}

int	is_died(t_main *main, int i)
{
	int	ret;

	pthread_mutex_lock(&main->decalre);
	if (i)
		main->is_died = i;
	ret = main->is_died;
	pthread_mutex_unlock(&main->decalre);
	return (ret);
}
