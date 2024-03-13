/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <psimarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 08:07:35 by psimarro          #+#    #+#             */
/*   Updated: 2024/03/13 11:49:54 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	launcher(t_program *program)
{
	pthread_t	*threads;
	int			i;

	i = -1;
	threads = malloc(sizeof(pthread_t) * program->n_philo);
	while (++i < program->n_philo)
	{
		if (!threads || \
			pthread_create(&threads[i], NULL, &routine, program->philos[i]))
			return (1);
	}
	check_philos(program);
	i = -1;
	while (++i < program->n_philo)
		pthread_join(threads[i], NULL);
	free(threads);
	free_philos(program, program->n_philo);
	return (0);
}

void	check_philos(t_program *program)
{
	int	i;
	int	eats;

	while (!(program->full) && !(program->dead))
	{
		i = -1;
		eats = 0;
		while (++i < program->n_philo)
		{
			pthread_mutex_lock(&program->philos[i]->eat_mutex);
			if ((ft_time() - program->philos[i]->t_last_eat) > program->t_die)
			{
				pthread_mutex_lock(&program->dead_lock);
				print_philo_dead(program->philos[i], "died");
				pthread_mutex_unlock(&program->dead_lock);
				pthread_mutex_unlock(&program->philos[i]->eat_mutex);
				return ;
			}
			if (program->philos[i]->n_eats >= program->n_eat)
				eats++;
			pthread_mutex_unlock(&program->philos[i]->eat_mutex);
		}
		if (program->n_eat != -1 && eats == program->n_philo)
			program->full = 1;
	}
}

static void	eat_and_release(t_philo *philo, int *dead)
{
	print_philo_state(philo, "has taken a fork");
	print_philo_state(philo, "has taken a fork");
	pthread_mutex_lock(&philo->eat_mutex);
	philo->t_last_eat = ft_time();
	philo->n_eats++;
	pthread_mutex_unlock(&philo->eat_mutex);
	print_philo_state(philo, "is eating");
	philo_sleep(philo->program->t_eat, dead);
	*philo->fork[1] = 0;
	pthread_mutex_unlock(&philo->right_lock);
	pthread_mutex_unlock(philo->left_lock);
}

static int	philo_eat(t_philo *philo, int *dead)
{
	pthread_mutex_lock(&philo->right_lock);
	if (*philo->fork[1] == 1)
	{
		pthread_mutex_unlock(&philo->right_lock);
		return (0);
	}
	*philo->fork[1] = 1;
	pthread_mutex_unlock(&philo->right_lock);
	pthread_mutex_lock(philo->left_lock);
	if (*philo->fork[0] == 1)
	{
		pthread_mutex_unlock(philo->left_lock);
		pthread_mutex_lock(&philo->right_lock);
		*philo->fork[1] = 0;
		pthread_mutex_unlock(&philo->right_lock);
		return (0);
	}
	pthread_mutex_lock(&philo->right_lock);
	eat_and_release(philo, dead);
	return (1);
}

void	*routine(void *data)
{
	t_philo		*philo;
	t_program	*program;

	philo = (t_philo *)data;
	program = philo->program;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!program->dead && !program->full)
	{
		if ((ft_time() - philo->t_last_eat) > philo->program->t_die)
		{
			pthread_mutex_lock(&program->dead_lock);
			print_philo_dead(philo, "died");
			pthread_mutex_unlock(&program->dead_lock);
			continue ;
		}
		if (program->dead || !(philo_eat(philo, &program->dead)))
			continue ;
		print_philo_state(philo, "is sleeping");
		philo_sleep(program->t_sleep, &program->dead);
		print_philo_state(philo, "is thinking");
	}
	return (NULL);
}
