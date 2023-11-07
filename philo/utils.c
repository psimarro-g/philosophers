/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <psimarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 10:56:17 by psimarro          #+#    #+#             */
/*   Updated: 2023/11/07 12:45:47 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	ft_error(char *str)
{
	write(2, str, ft_strlen(str));
	exit(1);
}

//get time in miliseconds
time_t	ft_time(void)
{
	struct timeval	time;
	time_t				ret;

	gettimeofday(&time, NULL);
	ret = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (ret);
}

void	check_err(t_program *program, int argc)
{
	if (program->n_philo < 1|| program->t_die < 0 || program->t_eat < 0
		|| program->t_sleep < 0)
	{
		printf("Error: invalid values\n");
		printf("Usage: ./philo n_philo t_die t_eat t_sleep [n_eat]\n");
		exit(1);
	}
	if (argc == 6 && program->n_eat <= 0)
	{
		printf("Error: invalid n_eat\n");
		printf("Usage: ./philo n_philo t_die t_eat t_sleep [n_eat]\n");
		exit(1);
	}
}