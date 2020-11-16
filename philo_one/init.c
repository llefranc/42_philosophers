/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 11:28:59 by lucaslefran       #+#    #+#             */
/*   Updated: 2020/11/16 12:07:06 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

/*
** Creates an array of threads (nb mutexs = nb philosophers).
*/
pthread_t	*create_philos(int	nb_philos, t_philo *ph)
{
	pthread_t		*thread;
	int				i;

	i = 0;
	if (!(thread = malloc(sizeof(*thread) * (nb_philos))))
		return (NULL);
	while (i < nb_philos)
		pthread_create(&thread[i++], NULL, &philo_life, ph); //penser a checker le retour d'erreur ?
	return (thread);
}

/*
** Creates an array of threads (nb mutexs = nb philosophers).
*/
pthread_mutex_t	*create_forks(int nb_forks, t_philo *ph)
{
	pthread_mutex_t	*mutex;
	int				i;

	i = 0;
	if (!(mutex = malloc(sizeof(*mutex) * (nb_forks))))
		return (NULL);
	while (i < nb_forks)
		pthread_mutex_init(&mutex[i++], NULL);
	pthread_mutex_init(&(ph->mutex_num_philo), NULL); //mutex for id_philo (see attributes_id_philo func)
	return (mutex);
}

/*
** Inits the different structure's arguments. Nb_each_philo_eat is set
** to -1 if the fifth argument is missing (optional argument).
*/
void	init_philo_struct(t_philo *ph, int ac, char **av)
{
	ph->nb_threads = ft_atoi(av[1]);
	ph->nb_philo = ph->nb_threads - 1;
	ph->t_to_die = ft_atoi(av[2]);
	ph->t_to_eat = ft_atoi(av[3]);
	ph->t_to_sleep = ft_atoi(av[4]);
	ph->nb_each_philo_eat = ac == 6 ? ft_atoi(av[5]) : -1;
	ph->time_start = get_time_ms(); //time reference for further time calculs
	ph->philo_die = 0;
}