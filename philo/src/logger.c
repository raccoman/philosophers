/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raccoman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 12:22:35 by raccoman          #+#    #+#             */
/*   Updated: 2021/09/21 12:23:05 by raccoman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_msg(t_philosopher *philo, size_t timestamp, int action)
{
	pthread_mutex_lock(&philo->instance->write_mutex);
	if (action == TAKING_FORK)
		printf("%zu %zu has taken a fork 🍽\n", timestamp, philo->position);
	else if (action == EATING)
		printf("%zu %zu is eating 🍕\n", timestamp, philo->position);
	else if (action == SLEEPING)
		printf("%zu %zu is sleeping 💤\n", timestamp, philo->position);
	else if (action == THINKING)
		printf("%zu %zu is thinking 💭\n", timestamp, philo->position);
	else if (action == DIED)
		printf("%zu %zu died 💀\n", timestamp, philo->position);
	else if (action == OVER)
		printf("%zu %zu has finished his meals 🤢\n", timestamp, philo->position);
	pthread_mutex_unlock(&philo->instance->write_mutex);
}

int	ft_log(int	error)
{
	if (error == WRONG_ARGUMENT)
		printf("Error: Wrong argument.\n");
	else if (error == TOO_MANY_ARGUMENTS)
		printf("Error: Wrong syntax.\n");
	else if (error == MALLOC_ERROR)
		printf("Error: Malloc error.\n");
	else if (error == PTHREAD_ERROR)
		printf("Error: PThread error.\n");
	return (1);
}
