/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <psimarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 08:07:35 by psimarro          #+#    #+#             */
/*   Updated: 2024/03/06 11:35:14 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

static void	kill_philos(t_program *program)
{
	int	i;
	int	status;

	i = -1;
	while (++i < program->n_philo)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		{
			i = -1;
			while (++i < program->n_philo)
				kill(program->philos[i]->proc_id, SIGTERM);
			break ;
		}
	}
	sem_close(program->forks);
	sem_close(program->write_lock);
	sem_close(program->dead_lock);
	sem_unlink("forks");
	sem_unlink("write_lock");
	sem_unlink("dead_lock");
}

int	launcher(t_program *program)
{
	int		i;
	t_philo	**philo;

	i = -1;
	philo = program->philos;
	while (++i < program->n_philo)
	{
		philo[i]->proc_id = fork();
		if (philo[i]->proc_id < 0)
			return (1);
		if (philo[i]->proc_id == 0)
			routine(philo[i]);
	}
	kill_philos(program);
	while (i < program->n_philo)
		free(program->philos[i++]);
	free(program->philos);
	return (0);
}

void	*check_philo(void *data)
{
	t_philo		*philo;
	t_program	*program;
	int			n_eats;

	philo = (t_philo *)data;
	program = philo->program;
	while (1)
	{
		if ((ft_time() - philo->t_last_eat) > program->t_die)
		{
			sem_wait(program->dead_lock);
			print_philo_state(philo, "died");
			program->dead = 1;
			sem_wait(program->write_lock);
			exit(1);
		}
		if (program->dead)
			break ;
		usleep(1000);
		if (philo->full)
			break ;
	}
	return (NULL);
}

static void	eat(t_philo *philo, int *dead)
{
	t_program	*program;

	program = philo->program;
	sem_wait(program->forks);
	print_philo_state(philo, "has taken a fork");
	sem_wait(program->forks);
	print_philo_state(philo, "has taken a fork");
	print_philo_state(philo, "is eating");
	philo->t_last_eat = ft_time();
	philo_sleep(program->t_eat, dead);
	if (program->n_eat != -1 && ++philo->n_eats == program->n_eat)
		philo->full = 1;
	sem_post(program->forks);
	sem_post(program->forks);
}

void	routine(t_philo *philo)
{
	t_program	*program;

	program = philo->program;
	if (pthread_create(&philo->dead_check, NULL, &check_philo, philo))
		exit(1);
	if (philo->id % 2 == 0)
		usleep(10000);
	while (!(program->dead))
	{
		eat(philo, &program->dead);
		if (philo->full)
			break ;
		print_philo_state(philo, "is sleeping");
		philo_sleep(program->t_sleep, &program->dead);
		print_philo_state(philo, "is thinking");
	}
	pthread_join(philo->dead_check, NULL);
	if (program->dead)
		exit(1);
	exit(0);
}
