/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 11:28:59 by lucaslefran       #+#    #+#             */
/*   Updated: 2020/11/17 20:05:41 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

/*
** Creates n child processes for n philosophers.
*/
void	launch_processes(t_philo *ph)
{
	int				i;
	pid_t			*pid;

	i = -1;
	if (!(pid = malloc(sizeof(*pid) * ph->info->nb_ph)))
		exit(error_msg("Fatal error : malloc failed\n")); //rajouter ici le free des sem + les free en general
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
	while (--i >= 0)
		kill(pid[i], SIGINT);
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
	ph->nb_forks = sem_open(S_FORKS, O_CREAT, 0644, info->nb_ph / 2); //divided by 2 because algo works with pairs of forks
	ph->printing = sem_open(S_PRINT, O_CREAT, 0644, 1);
	ph->take_forks = sem_open(S_TAKE, O_CREAT, 0644, 1);
	ph->ph_die = sem_open(S_PHILO_DIE, O_CREAT, 0644, 0); //unblock main process when a philosophe die
	return (SUCCESS);
}
