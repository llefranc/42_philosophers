/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 11:04:24 by lucaslefran       #+#    #+#             */
/*   Updated: 2020/11/18 19:24:33 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

/*
** Checks if the actual thread (philosophe) ate enough. If it's the case,
** checks if all the philosophers have eaten enough and stops the algorithm if
** it's the case.
*/
void	check_philo_is_fed(t_philo *ph, int *nb_of_time_ph_ate)
{
	sem_wait(ph->printing);
	if (++(*nb_of_time_ph_ate) == ph->info->nb_each_ph_eat) //if missing arg 5, nb_each_ph_eat == -1, will never be true
		sem_post(ph->nb_ph_fed);
	sem_post(ph->printing);
}

/*
** Locks a semaphore (= philospher picks 2 forks at a the same time) and then
** starts to eat for time_to_eat ms. Then unlocks the forks semaphore.
*/
void	philo_eat(t_philo *ph, int *nb_of_time_ph_ate)
{
	sem_wait(ph->nb_forks);                                              //philosopher take 2 forks at the same time
	print_state_msg(ph, ph->id, get_time_ms() - ph->time_start, FORK);
	print_state_msg(ph, ph->id, get_time_ms() - ph->time_start, FORK);
	ph->time_last_meal = get_time_ms();                                  //updating time when philosopher starts to eat
	print_state_msg(ph, ph->id, get_time_ms() - ph->time_start, EAT);    //eating when he has 2 forks
	check_philo_is_fed(ph, nb_of_time_ph_ate);
	better_sleep(ph->info->t_to_eat * 1000);                             //converting ms in microsec
	sem_post(ph->nb_forks);                                              //finished to eat, put back his two forks
	print_state_msg(ph, ph->id, get_time_ms() - ph->time_start, SLEEP);  //sleeping after eating
	better_sleep(ph->info->t_to_sleep * 1000);
	print_state_msg(ph, ph->id, get_time_ms() - ph->time_start, THINK);  //thinking after eating
}

/*
** Checks the time since last lunch, and if it's more than time_to_die prints
** the death message and sets ph_die boolean to 1 (it will prevent other
** messages from other threads to be print on screen), then exits.
*/
void	*check_philo_alive(void *tmp)
{
	long		time_death;
	t_philo		*ph;

	ph = (t_philo *)tmp;
	while (1)
	{
		time_death = get_time_ms();
		if ((time_death - ph->time_last_meal) > ph->info->t_to_die)
		{
			sem_wait(ph->printing); //only one thread prints at a time
			print_ms_and_state(ph->id, time_death - ph->time_start, " has died\n");
			sem_post(ph->ph_die);
			return (NULL);
		}
	}
}

/*
** Creates a thread for controlling time_to_die, and then executes
** eat -> sleep > think in a loop until a philosophe die, then exits.
*/
int		philo_life(t_philo *ph)
{
	pthread_t	control_die;
	int			nb_of_time_ph_ate;

	nb_of_time_ph_ate = 0;
	ph->time_last_meal = get_time_ms();
	pthread_create(&control_die, NULL, &check_philo_alive, (void *)ph); //thread to control time_to_die
	while (1)
		philo_eat(ph, &nb_of_time_ph_ate);
	exit(SUCCESS);
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
** Destroys all the semaphores and frees all the memory allocated.
*/
void	clean_exit(t_philo ph)
{
	sem_unlink(S_FORKS); //unlink prevents semaphore existing forever
	sem_unlink(S_PRINT);
	sem_unlink(S_TAKE);
	sem_unlink(S_PHILO_DIE);
	sem_unlink(S_NB_PH_FED);
	sem_close(ph.nb_forks);
	sem_close(ph.printing);
	sem_close(ph.take_forks);
	sem_close(ph.ph_die);
	sem_close(ph.nb_ph_fed);
}
