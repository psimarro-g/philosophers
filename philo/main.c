/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <psimarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 22:43:51 by psimarro          #+#    #+#             */
/*   Updated: 2024/03/07 09:35:35 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	free_philos(t_program *program, int id)
{
	int	i;

	i = 0;
	while (i < id)
	{
		pthread_mutex_destroy(&program->philos[i]->right_lock);
		free(program->philos[i]->fork[1]);
		free(program->philos[i++]);
	}
	{
		pthread_mutex_destroy(&program->philos[i]->right_lock);
		free(program->philos[i]->fork[1]);
		free(program->philos[i++]);
	}
	pthread_mutex_destroy(&program->write_lock);
	pthread_mutex_destroy(&program->dead_lock);
	free(program->philos);
}

int	main(int argc, char **argv)
{
	t_program	program;

	if (argc < 5 || argc > 6)
	{
		ft_perror("Wrong number of arguments\nUsage: \
				./philo n_philo t_die t_eat t_sleep [n_eat]");
		return (1);
	}
	program = parse_input(argc, argv);
	if (check_err(&program, argc))
	{
		pthread_mutex_destroy(&program.write_lock);
		pthread_mutex_destroy(&program.dead_lock);
		return (1);
	}
	program.philos = init_philos(&program);
	if (!program.philos)
		return (ft_perror("Error creating the philos"));
	if (launcher(&program))
	{
		free_philos(&program, program.n_philo);
		return (ft_perror("Error creating the threads"));
	}
	return (0);
}
