/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 11:28:59 by lucaslefran       #+#    #+#             */
/*   Updated: 2020/11/16 19:20:29 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

/*
** Creates an array of threads (nb mutexs = nb philosophers).
*/
void	launch_threads(int	nb_ph, t_philo *ph)
{
	int				i;

	i = -1;
	while (++i < nb_ph)
		pthread_create(&(ph[i].thread), NULL, &philo_life, &(ph[i])); //penser a checker le retour d'erreur ?
}

/*
** Creates an array of threads (nb mutexs = nb philosophers).
*/
pthread_mutex_t	*create_forks(int nb_forks)
{
	pthread_mutex_t	*mutex;
	int				i;

	i = 0;
	if (!(mutex = malloc(sizeof(*mutex) * (nb_forks))))
		return (NULL);
	while (i < nb_forks)
		pthread_mutex_init(&mutex[i++], NULL);
	// pthread_mutex_init(&(ph->mutex_num_ph), NULL); //mutex for id_philo (see attributes_id_philo func)
	return (mutex);
}

/*
** Inits the different structure's arguments. Nb_each_philo_eat is set
** to -1 if the fifth argument is missing (optional argument).
*/
void	init_t_info(t_info *info, int ac, char **av)
{
	info->nb_ph = ft_atoi(av[1]);
	info->t_to_die = ft_atoi(av[2]);
	info->t_to_eat = ft_atoi(av[3]);
	info->t_to_sleep = ft_atoi(av[4]);
	info->nb_each_ph_eat = ac == 6 ? ft_atoi(av[5]) : -1;
}

/*
** Creates, initiates and returns an array of struct t_philo. Returns NULL if
** an error occured.
*/
t_philo	*create_t_philo_array(pthread_mutex_t *mutex, t_pdata *ph_die, t_info *info)
{
	t_philo	*ph;
	int		nb_ph;
	long	time_start;
	
	nb_ph = info->nb_ph;
	if (!(ph = malloc(sizeof(*ph) * (nb_ph + 1)))) //+1 for NULL-terminated
		return (NULL);
	ph[nb_ph].id = 0; //end the array
	time_start = get_time_ms(); //ref time for time calculs
	while (nb_ph - 1 >= 0)
	{
		ph[nb_ph - 1].id = nb_ph;
		ph[nb_ph - 1].mutex = mutex;
		ph[nb_ph - 1].ph_die = ph_die;
		ph[nb_ph - 1].info = info;
		ph[nb_ph - 1].time_start = time_start; //all structs have the same time_start
		nb_ph--;
	}
	return (ph);
}