/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llefranc <llefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 11:28:59 by lucaslefran       #+#    #+#             */
/*   Updated: 2021/04/28 14:49:57 by llefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

/*
** If there is the optional argument (the 5th), sem_wait n time (for n philos)
** until all philos are fed, then sem_post the ph_die semaphore in order to
** unlock the main and ends the simulation. If no 5th argument, do nothing.
*/
void	*wait_until_all_fed(void *tmp)
{
	t_philo	*ph;
	int		i;
	
	ph = (t_philo *)tmp;
	i = ph->info->nb_ph;
	if (ph->info->nb_each_ph_eat != -1)
		while (--i >= 0) 
			sem_wait(ph->nb_ph_fed); //waiting until all philos are fed
	if (ph->info->nb_each_ph_eat != -1) //-1 for 5th argument missing but also if a philo is dead
	{
		sem_wait(ph->printing);
		sem_post(ph->ph_die); //unblock main
		ft_putstr_fd("All philosphers have eaten enough\n", 1);
	}
	return (tmp);
}

/*
** Creates n child processes for n philosophers.
*/
void	launch_processes(t_philo *ph)
{
	int				i;
	pid_t			*pid;
	pthread_t		control_nb_ph_fed;

	i = -1;
	if (!(pid = malloc(sizeof(*pid) * ph->info->nb_ph)))
		exit(error_msg("Fatal error : malloc failed\n"));
	pthread_create(&control_nb_ph_fed, NULL, &wait_until_all_fed, (void *)ph);
	while (++i < ph->info->nb_ph)
	{
		if ((pid[i] = fork()) < 0)
			exit(error_msg("Fatal error : fork failed\n"));
		else if (!pid[i]) //child
		{
			ph->id = i + 1;
			philo_life(ph);
		}
	}
	sem_wait(ph->ph_die);
	while (--i >= 0) //killing all children
		kill(pid[i], SIGINT);
	i = ph->info->nb_each_ph_eat; //in case a philo is dead before they are all fed
	ph->info->nb_each_ph_eat = -1;
	while (--i >= 0)
		sem_post(ph->nb_ph_fed); //we unblock the sem ih thread control_nb_ph_fed so we can close the semaphore
	free(pid);
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
int		create_t_philo_array(t_philo *ph, t_info *info)
{
	ph->time_start = get_time_ms(); //ref time for time calculs
	ph->info = info;
	sem_unlink(S_FORKS);
	sem_unlink(S_PRINT);
	sem_unlink(S_TAKE);
	sem_unlink(S_PHILO_DIE);
	sem_unlink(S_NB_PH_FED);
	ph->nb_forks = sem_open(S_FORKS, O_CREAT, 0644, info->nb_ph); //represents nb of forks
	ph->printing = sem_open(S_PRINT, O_CREAT, 0644, 1);
	ph->take_forks = sem_open(S_TAKE, O_CREAT, 0644, 1);
	ph->ph_die = sem_open(S_PHILO_DIE, O_CREAT, 0644, 0); //unblock main process when a philosophe die
	ph->nb_ph_fed = sem_open(S_NB_PH_FED, O_CREAT, 0644, 0); //unblock main process when all philo are fed
	return (SUCCESS);
}
