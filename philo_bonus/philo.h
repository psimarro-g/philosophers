/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <psimarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 22:45:31 by psimarro          #+#    #+#             */
/*   Updated: 2024/02/02 21:47:57 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <semaphore.h>
# include <limits.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>

struct	s_program;

typedef struct s_philo
{
	int					id;
	int					n_eats;
	time_t				t_last_eat;
	int					*fork[2];
	struct s_program	*program;
	pid_t				proc_id;
	pthread_t			dead;
}				t_philo;

typedef struct s_program
{
	int					n_philo;
	int					t_die;
	int					t_eat;
	int					t_sleep;
	int					n_eat;
	int					dead;
	time_t				t_start;
	sem_t				*forks;
	sem_t				*write_lock;
	sem_t				*eat;
	t_philo				**philos;
}				t_program;

/* INIT.C */
int			parse_input(t_program *program, int argc, char **argv);
t_philo		**init_philos(t_program *program);
void		ft_update_dead(t_philo *philo);

/* LAUNCH.C */
int			launcher(t_program *program);
void		*routine(void *data);
void		check_philos(t_program *program);

/* FT_PATOI.C */
int			ft_patoi(const char *str);

/* UTILS.C */
int			check_err(t_program *program, int argc);
int			ft_perror(char *str);
time_t		ft_time(void);
void		philo_sleep(time_t time, int *dead);
void		print_philo_state(t_philo *philo, char *str);

#endif
