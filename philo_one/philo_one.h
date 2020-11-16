/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 21:06:54 by lucaslefran       #+#    #+#             */
/*   Updated: 2020/11/16 12:01:33 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define SUCCESS 0
# define FAILURE 1

# define EAT 0
# define FORK 1
# define THINK 2
# define SLEEP 3
# define DIE 4

typedef struct		s_philo
{
	int				nb_threads;
	int				nb_philo;
	int				t_to_die;
	int				t_to_eat;
	int				t_to_sleep;
	int				nb_each_philo_eat;
	pthread_t		*thread;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	mutex_num_philo;
	long			time_start;
	int				philo_die;		//boolean sets to 1 when a philo die
}					t_philo;

//utils.c

int		check_arguments(int ac, char **av);
int		print_state_msg(t_philo *ph, int id_philo, suseconds_t ms, int type);
long	get_time_ms(void);

//libft.c

size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);
int		ft_strisdigit(char *str);
long	ft_atoi(const char *str);
char	*ft_itoa(long n);


//init.c

pthread_t	*create_philos(int	nb_philos, t_philo *ph);
pthread_mutex_t	*create_forks(int nb_forks, t_philo *ph);
void	init_philo_struct(t_philo *ph, int ac, char **av);

void	*philo_life(void *ph);

#endif