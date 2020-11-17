/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 21:06:54 by lucaslefran       #+#    #+#             */
/*   Updated: 2020/11/17 13:19:52 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>

# define SUCCESS 0
# define FAILURE 1

# define EAT 0
# define FORK 1
# define THINK 2
# define SLEEP 3
# define DIE 4

# define S_FORKS "sem_forks"
# define S_TAKE "sem_take_forks"
# define S_PRINT "sem_print"
# define S_PHILO_DIE "sem_philo_die"
typedef struct		s_info
{
	int				nb_ph;
	int				t_to_die;
	int				t_to_eat;
	int				t_to_sleep;
	int				nb_each_ph_eat;
}					t_info;

typedef struct		s_philo
{
	int				id;
	t_info			*info;
	pthread_t		thread;
	sem_t			*nb_forks;
	long			time_start;
	long			time_last_meal;
	sem_t			*printing;      //one thread at a time can print
	sem_t			*take_forks;    //one philo at a time can take 2 forks
	sem_t			*ph_die;        //main will block until a philo die
}					t_philo;

//utils.c

int				error_msg(char *str);
int				check_arguments(int ac, char **av);
int				print_ms_and_state(int id, int ms, char *str_msg);
int				print_state_msg(t_philo *ph, int id_philo, suseconds_t ms, int type);
long			get_time_ms(void);

//libft.c

size_t			ft_strlen(const char *s);
void			ft_putstr_fd(char *s, int fd);
int				ft_strisdigit(char *str);
long			ft_atoi(const char *str);
char			*ft_itoa(long n);
void			better_sleep(long d);
int				lennb(unsigned int nb);
int				lennb_for_str(unsigned int nb);
void			ft_putnbr_buffer(int n, char *str);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);

//init.c

void			init_t_info(t_info *info, int ac, char **av);
int				create_t_philo_array(t_philo *ph, t_info *info);
pthread_mutex_t	*create_forks(int nb_forks);
void			launch_processes(t_philo *ph);

//threads.c

int				philo_life(t_philo *ph);
void			join_all_threads(t_philo *ph);
void			clean_exit(t_philo ph);

#endif
