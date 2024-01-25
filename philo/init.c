/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <psimarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 08:09:20 by psimarro          #+#    #+#             */
/*   Updated: 2024/01/25 11:30:46 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

t_program   parse_input(int argc, char **argv)
{
    t_program   ret;

	memset(&ret, 0, sizeof(t_program));
	ret.n_philo = ft_patoi(argv[1]);
    ret.t_die = ft_patoi(argv[2]);
	ret.t_eat = ft_patoi(argv[3]);
	ret.t_sleep = ft_patoi(argv[4]);
	ret.t_start = ft_time();
	if (argc == 6)
		ret.n_eat = ft_patoi(argv[5]);
	else
		ret.n_eat = -1;
	ret.dead = 0;
	ret.full = 0;
	pthread_mutex_init(&ret.write_lock, NULL);
	pthread_mutex_init(&ret.dead_lock, NULL);
	return (ret);
}
t_philo	*create_philos(t_program *program, int id)
{
	t_philo *philo;

	philo = (t_philo*)malloc(sizeof(t_philo));
	philo->id = id;
	philo->n_eats = 0;
	philo->t_last_eat = program->t_start;
	philo->fork[1] = malloc(sizeof(int));
	*philo->fork[1] = 0;
	pthread_mutex_init(&philo->right_lock, NULL);
	philo->program = program;
	return (philo);
}

t_philo	**init_philos(t_program  *program)
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
	i = 0;
	while (i < program->n_philo)
	{
		philos[i]->left_lock = &philos[(i + 1) % program->n_philo]->right_lock;
		philos[i]->fork[0] = philos[(i + 1) % program->n_philo]->fork[1];
		i++;
	}
	return (philos);
}
