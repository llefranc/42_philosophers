/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 21:06:40 by lucaslefran       #+#    #+#             */
/*   Updated: 2020/11/17 13:18:50 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		main(int ac, char **av)
{
	t_philo			*ph;
	t_pdata			ph_die;
	pthread_mutex_t	*mutex;
	t_info			info;
	
	if (check_arguments(ac, av))
		return (FAILURE);
	pthread_mutex_init(&(ph_die.mutex), NULL);
	ph_die.data = 0;
	init_t_info(&info, ac, av);
	if (info.nb_ph < 2)
		return (error_msg("Not enough philosphers, must be at least 2\n"));
	mutex = create_forks(info.nb_ph); //creates x mutexs for x philosophers
	if (!(ph = create_t_philo_array(mutex, &ph_die, &info)))
		return (error_msg("Malloc failed\n"));
	launch_threads(ph);
	join_all_threads(ph); //waiting all threads
	clean_exit(ph);
	return (0);
}
