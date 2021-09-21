/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raccoman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 12:24:05 by raccoman          #+#    #+#             */
/*   Updated: 2021/09/21 12:24:06 by raccoman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "philosophers.h"

int	clear(t_main *instance)
{
	size_t	i;

	i = 0;
	while (i < instance->amount)
		kill(instance->philosophers[i++].pid, SIGKILL);
	free(instance->philosophers);
	return (0);
}

int	init_sem(t_main *instance)
{
	sem_unlink("forks");
	sem_unlink("write");
	sem_unlink("die");
	instance->frks_sem = sem_open("forks", O_CREAT, 0644, instance->amount);
	instance->write_sem = sem_open("write", O_CREAT, 0644, 1);
	instance->die_sem = sem_open("die", O_CREAT, 0644, 0);
	return (0);
}

int	init_philosophers(t_main *instance)
{
	size_t	i;

	instance->philosophers = malloc(sizeof(t_philosopher) * instance->amount);
	if (!instance->philosophers)
		return (ft_log(MALLOC_ERROR));
	i = 0;
	while (i < instance->amount)
	{
		instance->philosophers[i].position = i;
		instance->philosophers[i].meals = 0;
		instance->philosophers[i].eating = 0;
		instance->philosophers[i].instance = instance;
		i++;
	}
	return (0);
}

int	init_args(t_main *instance, int argc, const char **argv)
{
	if (argc < 5 || argc > 6)
		return (ft_log(TOO_MANY_ARGUMENTS));
	if (ft_atol(argv[1], &instance->amount) || instance->amount == 0
		|| ft_atol(argv[2], &instance->ttdie) || instance->ttdie == 0
		|| ft_atol(argv[3], &instance->tteat) || instance->tteat == 0
		|| ft_atol(argv[4], &instance->ttsleep) || instance->ttsleep == 0)
		return (ft_log(WRONG_ARGUMENT));
	if (argc == 6 && (ft_atol(argv[5], &instance->meals)
			|| instance->meals == 0))
		return (ft_log(WRONG_ARGUMENT));
	else if (argc == 5)
		instance->meals = -1;
	instance->finished = 0;
	return (0);
}

int	main(int argc, const char **argv)
{
	t_main	instance;

	if (init_args(&instance, argc, argv)
		|| init_philosophers(&instance)
		|| init_sem(&instance))
		return (1);
	if (start(&instance))
		return (1);
	sem_wait(instance.die_sem);
	clear(&instance);
}
