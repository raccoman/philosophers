/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raccoman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 12:24:12 by raccoman          #+#    #+#             */
/*   Updated: 2021/09/21 12:24:14 by raccoman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *vphilo)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)vphilo;
	philo->last_meal = get_time();
	philo->threshold = philo->last_meal + philo->instance->ttdie;
	while (1)
	{
		if (take_forks(philo) || eat(philo) || release_forks(philo))
			break ;
	}
	return (NULL);
}
