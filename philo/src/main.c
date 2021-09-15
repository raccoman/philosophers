#include "philosophers.h"

int	clear(t_main *instance)
{
	size_t	i;

	i = 0;
	while (i < instance->amount)
	{
		pthread_mutex_destroy(&instance->frks_mutexes[i]);
		i++;
	}
	pthread_mutex_destroy(&instance->write_mutex);
	pthread_mutex_destroy(&instance->die_mutex);
	free(instance->frks_mutexes);
	free(instance->philosophers);
	free(instance->forks);
	return (0);
}

int	init_mutexes(t_main *instance)
{
	size_t	i;

	instance->frks_mutexes = malloc(sizeof(pthread_mutex_t)
			* instance->amount);
	if (!instance->frks_mutexes)
		return (ft_log(MALLOC_ERROR));
	i = 0;
	while (i < instance->amount)
	{
		pthread_mutex_init(&instance->frks_mutexes[i], NULL);
		i++;
	}
	pthread_mutex_init(&instance->write_mutex, NULL);
	pthread_mutex_init(&instance->die_mutex, NULL);
	return (0);
}

int	init_philosophers(t_main *instance)
{
	size_t	i;

	instance->philosophers = malloc(sizeof(t_philosopher) * instance->amount);
	instance->forks = malloc(sizeof(int) * instance->amount);
	if (!instance->philosophers || !instance->forks)
		return (ft_log(MALLOC_ERROR));
	i = 0;
	while (i < instance->amount)
	{
		instance->forks[i] = 0;
		instance->philosophers[i].position = i;
		instance->philosophers[i].l_fork = i;
		instance->philosophers[i].r_fork = (i + 1) % instance->amount;
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
		|| init_mutexes(&instance))
		return (1);
	if (start(&instance))
		return (1);
	pthread_mutex_lock(&instance.die_mutex);
	pthread_mutex_unlock(&instance.die_mutex);
	clear(&instance);
	exit(0);
}
