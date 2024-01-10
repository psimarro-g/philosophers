/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <psimarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 08:07:35 by psimarro          #+#    #+#             */
/*   Updated: 2024/01/10 21:39:59 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int launcher(t_program *program)
{
    pthread_t   *threads;
    int         i;

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
		pthread_mutex_destroy(&program->philos[i]->eat_mutex);
        i++;
    }
    return (0);
}

void	check_philos(t_program *program)
{
	int i;

	while (!(program->full))
	{
		i = 0;
		while (!(program->dead) && i < program->n_philo)
		{
			pthread_mutex_lock(&program->philos[i]->eat_mutex);
			if (ft_time() - program->philos[i]->t_last_eat > program->t_die)
			{
				print_philo_state(program->philos[i], "died");
				program->dead = 1;
			}
			pthread_mutex_unlock(&program->philos[i++]->eat_mutex);
		}
		if (program->dead)
			return ;
		i = 0;
		while (program->n_eat != -1 && i < program->n_philo && \
				program->philos[i]->n_eats >= program->n_eat)
			i++;
		if (i == program->n_philo)
			program->full = 1;
	}

}

static void eat_and_release(t_philo *philo, int *dead)
{
	pthread_mutex_lock(&philo->eat_mutex);
	print_philo_state(philo, "is eating");
	philo->t_last_eat = ft_time();
	pthread_mutex_unlock(&philo->eat_mutex);
	philo_sleep(philo->program->t_eat, dead);
	philo->n_eats++;
	pthread_mutex_lock(&philo->right_lock);
		*philo->fork[1] = 0;
	pthread_mutex_unlock(&philo->right_lock);
	pthread_mutex_lock(philo->left_lock);
		*philo->fork[0] = 0;
	pthread_mutex_unlock(philo->left_lock);
}

static int philo_eat(t_philo *philo, int *dead)
{
	pthread_mutex_lock(&philo->right_lock);
	if (*philo->fork[1] == 1)
	{
		pthread_mutex_unlock(&philo->right_lock);
		return (0);
	}
	*philo->fork[1] = 1;
	print_philo_state(philo, "has taken a fork");
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
	*philo->fork[0] = 1;
	print_philo_state(philo, "has taken a fork");
	eat_and_release(philo, dead);
	return (1);
}

void	*routine(void *data)
{
    int			i;
    t_philo		*philo;
    t_program	*program;

    philo = (t_philo*)data;
	program = philo->program;
	i = 0;
	if (philo->id % 2 == 0)
		usleep(10000);
	while (!(program->dead))
	{
		if (!(philo_eat(philo, &program->dead)))
			continue ;
		if (program->full)
			break ;
		print_philo_state(philo, "is sleeping");
		philo_sleep(program->t_sleep, &program->dead);
		print_philo_state(philo, "is thinking");
		i++;
	}
    return (NULL);
}
