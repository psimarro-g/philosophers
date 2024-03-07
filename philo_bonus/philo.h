/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psimarro <psimarro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 22:45:31 by psimarro          #+#    #+#             */
/*   Updated: 2024/03/07 10:13:04 by psimarro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <fcntl.h>
# include <limits.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>

struct	s_program;

typedef struct s_philo
{
	int					id;
	int					n_eats;
	int					full;
	time_t				t_last_eat;
	struct s_program	*program;
	pid_t				proc_id;
	pthread_t			dead_check;
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
	sem_t				*meals;
	sem_t				*dead_lock;
	t_philo				**philos;
}				t_program;

/* MAIN.C */
void		free_philos(t_program *program, int id);

/* INIT.C */
int			parse_input(t_program *program, int argc, char **argv);
t_philo		**init_philos(t_program *program);
void		ft_update_dead(t_philo *philo);

/* LAUNCH.C */
int			launcher(t_program *program);
void		routine(t_philo *philo);
void		*check_philo(void *data);

/* FT_PATOI.C */
int			ft_patoi(const char *str);

/* UTILS.C */
int			check_err(t_program *program, int argc);
int			ft_perror(char *str);
time_t		ft_time(void);
void		philo_sleep(time_t time, int *dead);
void		print_philo_state(t_philo *philo, char *str);

#endif
