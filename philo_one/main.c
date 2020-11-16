/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 21:06:40 by lucaslefran       #+#    #+#             */
/*   Updated: 2020/11/16 12:07:36 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

/*
** Attributes to each thread an unique philosopher number (between 0 and
** nb_philo -1) in order to navigates in the threads / mutexs array previously
** created.
*/
int		attributes_id_philo(t_philo *ph)
{
	int		id_philo;
	
	pthread_mutex_lock(&(ph->mutex_num_philo));
	id_philo = (ph->nb_philo)--;
	pthread_mutex_unlock(&(ph->mutex_num_philo));
	return (id_philo);
}

/*
** For philospher number x, locks mutex x and mutex x-1. When the 2 mutexs are
** lock, the philosopher starts to eat for time_to_eat ms. Then unlocks the 2
** mutexs.
*/
void	philo_eat(int id_philo, t_philo *ph)
{
	int		id_fork;

	id_fork = id_philo != 0 ? id_philo - 1 : ph->nb_threads - 1; //if philo num 0, will take fork 0 and fork n (for n philosphers)
	if (!pthread_mutex_lock(&((ph->mutex)[id_philo])))
		print_state_msg(ph, id_philo, get_time_ms() - ph->time_start, FORK);
	if (!pthread_mutex_lock(&((ph->mutex)[id_fork])))
		print_state_msg(ph, id_philo, get_time_ms() - ph->time_start, FORK);
	print_state_msg(ph, id_philo, get_time_ms() - ph->time_start, EAT); //eating when he has 2 forks
	usleep(ph->t_to_eat * 1000);
	pthread_mutex_unlock(&((ph->mutex)[id_philo]));
		// printf("%d : unlock id_philo %d\n", id_philo, id_philo);
	pthread_mutex_unlock(&((ph->mutex)[id_fork]));
		// printf("%d : unlock id_fork %d\n", id_philo, id_fork);
	print_state_msg(ph, id_philo, get_time_ms() - ph->time_start, SLEEP); //sleeping after eating
	usleep(ph->t_to_sleep * 1000);
	print_state_msg(ph, id_philo, get_time_ms() - ph->time_start, THINK); //thinking after eating
}

// void	*check_philo_alive(void *tmp)
// {
// 	t_philo		*ph;

// 	ph = (t_philo *)tmp;
// 	while (1)
// 	{
// 		if (get_time_ms()
// 	}
// }

void	*philo_life(void *ph)
{
	int		id_philo;

	id_philo = attributes_id_philo((t_philo *)ph); //index for threads / mutexs array
	while (1)
	{
		philo_eat(id_philo, (t_philo *)ph);
	}
	return (ph);
}

void	join_all_threads(t_philo *ph)
{
	int		i = -1;

	while (++i < ph->nb_threads)
		pthread_join((ph->thread)[i], NULL);
}

// manger > dormir > penser
//time_to_die : en millisecondes. Si un philosophe ne commence pas a manger
// dans ’time_to_die’ millisecondes après avoir commencer son dernier repas ou
// le début de la simulation, il meurt.

// Philosophe 1 est à coté de philosophe ’number_of_philosopher’. Tous les autres
// philosophes sont N sont à coté de leur N + 1 et N - 1.

// Le statut affiché ne doit pas être mélangé avec le statut d’un autre philosophe.
// • Vous ne pouvez pas avoir plus de 10ms de retard entre la mort d’un philosophe et
// l’affichage de sa mort.

//penser a checker les retours d'erreurs
//ameliorer le print (moins de write)

int		main(int ac, char **av)
{
	t_philo		ph;
	
	if (check_arguments(ac, av))
		return (FAILURE);
	init_philo_struct(&ph, ac, av); //atoi the 4 or 5 arguments into the struct

	ph.mutex = create_forks(ph.nb_threads, &ph); //creates x mutexs for x philosophers
	ph.thread = create_philos(ph.nb_threads, &ph); //creates x threads for x philosophers

	join_all_threads(&ph); //waiting all threads to finish
	free(ph.thread);
	free(ph.mutex);
	return (0);
}