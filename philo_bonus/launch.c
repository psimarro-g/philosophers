/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <psimarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 08:07:35 by psimarro          #+#    #+#             */
/*   Updated: 2024/02/02 20:53:23 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	launcher(t_program *program)
{
	pthread_t	*threads;
	int			i;

	i = 0;
	threads = malloc(sizeof(pthread_t) * program->n_philo);
	while (i < program->n_philo)
	{
		if (pthread_create(&threads[i], NULL, &routine, program->philos[i]))
			return (1);
		i++;
	}
	check_philos(program);
	i = 0;
	while (i < program->n_philo)
	{
		pthread_join(threads[i], NULL);
		pthread_mutex_destroy(&program->philos[i]->right_lock);
		free(program->philos[i]->fork[1]);
		free(program->philos[i++]);
	}
	pthread_mutex_destroy(&program->write_lock);
	free(program->philos);
	free(threads);
	return (0);
}

void	check_philos(t_program *program)
{
	int	i;
	int	n_eats;

	while (!(program->full))
	{
		if (program->dead)
			return ;
		i = 0;
		n_eats = 0;
		while (i < program->n_philo)
		{
			if ((ft_time() - program->philos[i]->t_last_eat) > program->t_die)
				ft_update_dead(program->philos[i]);
			if (program->philos[i]->n_eats >= program->n_eat)
				n_eats++;
			i++;
		}
		if (program->n_eat != -1 && n_eats == program->n_philo)
			program->full = 1;
	}
}

static void	eat_and_release(t_philo *philo, int *dead)
{
	print_philo_state(philo, "has taken a fork");
	print_philo_state(philo, "has taken a fork");
	if ((ft_time() - philo->t_last_eat) > philo->program->t_die)
		ft_update_dead(philo);
	philo->t_last_eat = ft_time();
	philo->n_eats++;
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
	while (!(program->dead))
	{
		if (program->n_philo == 1)
			continue ;
		if (!(philo_eat(philo, &program->dead)))
			continue ;
		if (program->full)
			break ;
		print_philo_state(philo, "is sleeping");
		philo_sleep(program->t_sleep, &program->dead);
		print_philo_state(philo, "is thinking");
	}
	return (NULL);
}
