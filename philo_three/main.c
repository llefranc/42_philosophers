/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 21:06:40 by lucaslefran       #+#    #+#             */
/*   Updated: 2020/11/17 19:53:57 by lucaslefran      ###   ########.fr       */
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
	create_t_philo_array(&ph, &info); // > ok
	launch_processes(&ph); //> j'en suis dans philo life
	// join_all_threads(ph); //waiting all threads
	clean_exit(ph); //a modifier
	return (0);
}
