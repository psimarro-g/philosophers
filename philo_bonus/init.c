/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <psimarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 08:09:20 by psimarro          #+#    #+#             */
/*   Updated: 2024/02/06 21:09:51 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	parse_input(t_program *program, int argc, char **argv)
{
	program->n_philo = ft_patoi(argv[1]);
	program->t_die = ft_patoi(argv[2]);
	program->t_eat = ft_patoi(argv[3]);
	program->t_sleep = ft_patoi(argv[4]);
	program->t_start = ft_time();
	if (argc == 6)
		program->n_eat = ft_patoi(argv[5]);
	else
		program->n_eat = -1;
	program->dead = 0;
	program->forks = sem_open("forks", O_CREAT, 0644, program->n_philo);
	program->write_lock = sem_open("write_lock", O_CREAT, 0644, 1);
	if (program->forks <= 0 || program->write_lock <= 0)
		return (1);
	return (0);
}

t_philo	*create_philos(t_program *program, int id)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	philo->id = id;
	philo->n_eats = 0;
	philo->t_last_eat = program->t_start;
	philo->program = program;
	return (philo);
}

t_philo	**init_philos(t_program *program)
{
	t_philo **philos;
	int 	i;

	i = 0;
	philos = (t_philo**)malloc(program->n_philo * sizeof(t_philo));
	while (i < program->n_philo)
	{
		philos[i] = create_philos(program, i + 1);
		i++;
	}
	return (philos);
}

void	ft_update_dead(t_philo *philo)
{
	if (philo->program->dead)
		return ;
	printf("%ld %i died\n", ft_time() - \
	philo->program->t_start, philo->id);
	philo->program->dead = 1;
}
