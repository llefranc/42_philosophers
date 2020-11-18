/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 21:06:40 by lucaslefran       #+#    #+#             */
/*   Updated: 2020/11/18 12:52:14 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		main(int ac, char **av)
{
	t_philo			ph;
	t_info			info;
	
	if (check_arguments(ac, av))
		return (FAILURE);
	init_t_info(&info, ac, av);
	if (info.nb_ph < 2)
		return (error_msg("Not enough philosphers, must be at least 2\n"));
	create_t_philo_array(&ph, &info);
	launch_processes(&ph);
	clean_exit(ph);
	return (0);
}
