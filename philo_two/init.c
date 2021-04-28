/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 11:28:59 by lucaslefran       #+#    #+#             */
/*   Updated: 2021/04/28 14:41:01 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

/*
** Creates an array of threads.
*/
void	launch_threads(t_philo *ph)
{
	int				i;

	i = -1;
	while (ph[++i].id)
		pthread_create(&(ph[i].thread), NULL, &philo_life, &(ph[i]));
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
** Opens all the semaphore.
*/
int		init_semaphore(t_philo *ph, t_info *info)
{
	int		nb_ph;
	sem_t	*nb_forks;
	sem_t	*printing;
	sem_t	*take_forks;

	nb_ph = info->nb_ph;
	printing = NULL;
	sem_unlink(S_FORKS);
	sem_unlink(S_PRINT);
	sem_unlink(S_TAKE);
	nb_forks = sem_open(S_FORKS, O_CREAT, 0644, nb_ph); //represents nb of forks
	printing = sem_open(S_PRINT, O_CREAT, 0644, 1);
	take_forks = sem_open(S_TAKE, O_CREAT, 0644, 1);
	while (--nb_ph >= 0)
	{
		(ph[nb_ph]).nb_forks = nb_forks; //nb of pair of forks available
		(ph[nb_ph]).printing = printing; //one thread at a time can print
		(ph[nb_ph]).take_forks = take_forks; //one philo at a time can take 2 forks
	}
	return (SUCCESS);
}

/*
** Creates, initiates and returns an array of struct t_philo. Returns NULL if
** an error occured.
*/
t_philo	*create_t_philo_array(t_info *info, int *nb_ph_fed, int *ph_die)
{
	t_philo	*ph;
	int		nb_ph;
	long	time_start;
	
	nb_ph = info->nb_ph;
	if (!(ph = malloc(sizeof(*ph) * (nb_ph + 1)))) //+1 for NULL-terminated
		return (NULL);
	ph[nb_ph].id = 0; //end the array
	init_semaphore(ph, info);
	time_start = get_time_ms(); //ref time for time calculs
	while (nb_ph - 1 >= 0)
	{
		ph[nb_ph - 1].id = nb_ph;
		ph[nb_ph - 1].info = info;
		ph[nb_ph - 1].time_start = time_start; //all structs have the same time_start
		ph[nb_ph - 1].ph_die = ph_die;
		ph[nb_ph - 1].nb_ph_fed = nb_ph_fed;
		nb_ph--;
	}
	return (ph);
}