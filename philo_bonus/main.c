/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <psimarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 22:43:51 by psimarro          #+#    #+#             */
/*   Updated: 2024/02/06 21:18:34 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	main(int argc, char **argv)
{
	t_program	program;

	if (argc < 5 || argc > 6)
	{
		ft_perror("Error: Wrong number of arguments\n");
		ft_perror("Usage: ./philo n_philo t_die t_eat t_sleep [n_eat]\n");
		return (1);
	}
	memset(&program, 0, sizeof(t_program));
	if (parse_input(&program, argc, argv))
		return (1);
	if (check_err(&program, argc))
		return (1);
	program.philos = init_philos(&program);
	if (launcher(&program))
		return (ft_perror("Error creating the forks\n"));
	return (0);
}
