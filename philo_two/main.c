/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 21:06:40 by lucaslefran       #+#    #+#             */
/*   Updated: 2020/11/17 13:19:30 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int		main(int ac, char **av)
{
	t_philo			*ph;
	t_info			info;
	int				ph_die;
	
	if (check_arguments(ac, av))
		return (FAILURE);
	ph_die = 0;
	init_t_info(&info, ac, av);
	if (info.nb_ph < 2)
		return (error_msg("Not enough philosphers, must be at least 2\n"));
	if (!(ph = create_t_philo_array(&info, &ph_die)))
		return (error_msg("Malloc failed\n"));
	launch_threads(ph);
	join_all_threads(ph); //waiting all threads
	clean_exit(ph);
	return (0);
}
