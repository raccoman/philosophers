#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>

# define WRONG_ARGUMENT -1
# define TOO_MANY_ARGUMENTS -2
# define MALLOC_ERROR -3
# define PTHREAD_ERROR -4

struct	s_main;

typedef enum e_action
{
	TAKING_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DIED,
	OVER,
}				t_action;

typedef struct s_philosopher
{
	size_t			position;
	size_t			meals;
	size_t			eating;
	size_t			last_meal;
	size_t			threshold;
	pid_t			pid;
	struct s_main	*instance;
}				t_philosopher;

typedef struct s_main
{
	size_t			amount;
	size_t			tteat;
	size_t			ttdie;
	size_t			ttsleep;
	size_t			meals;
	size_t			finished;
	t_philosopher	*philosophers;
	sem_t			*write_sem;
	sem_t			*frks_sem;
	sem_t			*die_sem;
	pid_t			pid;
}				t_main;

int		ft_atol(const char *string, size_t *dst);
void	ft_msg(t_philosopher *philo, size_t timestamp, int action);
int		ft_log(int	error);
size_t	get_time(void);
void	*routine(void *vphilo);
int		start(t_main **instance);
int		take_forks(t_philosopher *philo);
int		eat(t_philosopher *philo);
int		release_forks(t_philosopher *philo);
void	ft_usleep(size_t ms);
void	*wait_children(void *vinstance);

#endif
