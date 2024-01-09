/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <psimarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 08:07:35 by psimarro          #+#    #+#             */
/*   Updated: 2024/01/09 21:28:57 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int launcher(t_program *program)
{
    pthread_t   *threads;
    int         i;

    i = 0;
    program->t_start = ft_time();
    threads = malloc(sizeof(pthread_t) * program->n_philo);
    while (i < program->n_philo)
    {
        if (pthread_create(&threads[i], NULL, &routine, program->philos[i]))
            return (1);
        i++;
    }
    //check_philos(program);
    i = 0;
    while (i < program->n_philo)
    {
        pthread_join(threads[i], NULL);
        pthread_mutex_destroy(&program->philos[i]->right_lock);
        i++;
    }
    pthread_mutex_destroy(&program->full_mutex);
    pthread_mutex_destroy(&program->dead_mutex);
    return (0);
}

void	*routine(void *data)
{
    
    return (NULL);
}
