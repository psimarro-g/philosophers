/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 22:43:51 by psimarro          #+#    #+#             */
/*   Updated: 2023/11/21 17:26:19 by psimarro         ###   ########.fr       */
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
	if (argc == 6)
		ret.n_eat = ft_patoi(argv[5]);
	else
		ret.n_eat = -1;
	ret.dead = 0;
	ret.full = 0; 
	ret.t_start = ft_time();
	return (ret);
}

int main(int argc, char **argv)
{
    t_program   program;

    if (argc < 5 || argc > 6)
	{
		printf("Error: Wrong number of arguments\n");
		printf("Usage: ./philo n_philo t_die t_eat t_sleep [n_eat]\n");
		return (1);
	}
	program = parse_input(argc, argv);
    check_err(&program, argc);
    return (0);
}