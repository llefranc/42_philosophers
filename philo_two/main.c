/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 21:06:40 by lucaslefran       #+#    #+#             */
/*   Updated: 2020/11/18 17:59:08 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int		main(int ac, char **av)
{
	t_philo			*ph;
	t_info			info;
	int				ph_die;
	int				nb_ph_fed;
	
	if (check_arguments(ac, av))
		return (FAILURE);
	ph_die = 0;
	nb_ph_fed = 0;
	init_t_info(&info, ac, av);
	if (info.nb_ph < 2)
		return (error_msg("Not enough philosphers, must be at least 2\n"));
	if (!(ph = create_t_philo_array(&info, &nb_ph_fed, &ph_die)))
		return (error_msg("Malloc failed\n"));
	launch_threads(ph);
	join_all_threads(ph); //waiting all threads
	clean_exit(ph);
	return (0);
}
