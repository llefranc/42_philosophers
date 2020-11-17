/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 11:04:24 by lucaslefran       #+#    #+#             */
/*   Updated: 2020/11/17 13:25:38 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

/*
** For philospher number x, locks mutex x and mutex x-1. When the 2 mutexs are
** lock, the philosopher starts to eat for time_to_eat ms. Then unlocks the 2
** mutexs. Odds philosophers id will start with rigth fork, even will start
** with left in order so the algo will not be block if all the philosophers
** take one fork exactly at the same time.
*/
void	philo_eat(t_philo *ph)
{
	int		right_f;
	int		left_f;

	right_f = ph->id - 1;
	left_f = right_f != 0 ? right_f - 1 : ph->info->nb_ph - 1; //if philo num 0, will take fork 0 and fork n (for n philosphers)
	if ((ph->id % 2 == 0 && !pthread_mutex_lock(&((ph->mutex)[left_f]))) //even id starts with left, odd id with right
			|| !pthread_mutex_lock(&((ph->mutex)[right_f])))
		print_state_msg(ph, ph->id, get_time_ms() - ph->time_start, FORK);
	if ((ph->id % 2 == 0 && !pthread_mutex_lock(&((ph->mutex)[right_f])))
			|| !pthread_mutex_lock(&((ph->mutex)[left_f])))
		print_state_msg(ph, ph->id, get_time_ms() - ph->time_start, FORK);
	ph->time_last_meal = get_time_ms(); //updating time when philosopher starts to eat
	print_state_msg(ph, ph->id, get_time_ms() - ph->time_start, EAT); //eating when he has 2 forks
	better_sleep(ph->info->t_to_eat * 1000); //converting ms in microsec
	pthread_mutex_unlock(&((ph->mutex)[left_f]));
	pthread_mutex_unlock(&((ph->mutex)[right_f]));
	print_state_msg(ph, ph->id, get_time_ms() - ph->time_start, SLEEP); //sleeping after eating
	better_sleep(ph->info->t_to_sleep * 1000);
	print_state_msg(ph, ph->id, get_time_ms() - ph->time_start, THINK); //thinking after eating
}

/*
** Checks the time since last lunch, and if it's more than time_to_die prints
** the death message and sets ph_die boolean to 1 (it will prevent other
** messages from other threads to be print on screen), then exits.
*/
void	*check_philo_alive(void *tmp)
{
	t_philo		*ph;
	long		time_death;

	ph = (t_philo *)tmp;
	while (1)
	{
		time_death = get_time_ms();
		if ((time_death - ph->time_last_meal) > ph->info->t_to_die)
		{
			pthread_mutex_lock(&(ph->ph_die->mutex)); //only one thread prints at a time
			if (!ph->ph_die->data) //doesn't print msg if another philo is already dead
				print_ms_and_state(ph->id, time_death - ph->time_start, " has died\n");
			ph->ph_die->data = 1; //sets death boolean to 1, no other messages from other philo will be print
			pthread_mutex_unlock(&(ph->ph_die->mutex));
			return (NULL);
		}
	}
}

/*
** Creates a thread for controlling time_to_die, and then executes
** eat -> sleep > think in a loop until a philosophe die, then exits.
*/
void	*philo_life(void *ph)
{
	pthread_t	control_die;

	((t_philo *)ph)->time_last_meal = get_time_ms();
	pthread_create(&control_die, NULL, &check_philo_alive, ph); //thread to control time_to_die
	while (1)
	{
		philo_eat((t_philo *)ph);
		if (((t_philo *)ph)->ph_die->data) //if a philo is dead, the thread exits
		{
			pthread_join(control_die, NULL);
			return (ph);
		}
	}
	return (ph);
}

/*
** Joins each threads created.
*/
void	join_all_threads(t_philo *ph)
{
	int		i = -1;

	while (ph[++i].id)
		pthread_join(ph[i].thread, NULL);
}

/*
** Destroys all the mutexs and frees all the memory allocated.
*/
void	clean_exit(t_philo *ph)
{
	int		i;

	i = -1;
	while (ph[++i].id)
		pthread_mutex_destroy(&((ph[i].mutex)[i]));
	pthread_mutex_destroy(&(ph->ph_die->mutex));
	free(ph->mutex);
	free(ph);
}
