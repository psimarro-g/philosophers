/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <psimarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 22:43:51 by psimarro          #+#    #+#             */
/*   Updated: 2024/03/07 10:13:56 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	free_philos(t_program *program, int id)
{
	int	i;

	i = 0;
	while (i < id)
	{
		free(program->philos[i++]);
	}
	sem_unlink("/forks");
	sem_unlink("/write_lock");
	sem_unlink("/dead_lock");
	free(program->philos);
}

int	main(int argc, char **argv)
{
	t_program	program;
	int			i;

	i = 0;
	if (argc < 5 || argc > 6)
	{
		ft_perror("Error: Wrong number of arguments\n");
		ft_perror("Usage: ./philo n_philo t_die t_eat t_sleep [n_eat]\n");
		return (1);
	}
	if (parse_input(&program, argc, argv))
		return (1);
	if (check_err(&program, argc))
	{
		sem_unlink("/forks");
		sem_unlink("/write_lock");
		sem_unlink("/dead_lock");
		return (1);
	}
	program.philos = init_philos(&program);
	if (!program.philos)
		return (1);
	if (launcher(&program))
		return (ft_perror("Error creating the forks\n"));
	return (0);
}
