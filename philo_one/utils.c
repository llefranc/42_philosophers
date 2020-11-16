/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 21:08:56 by lucaslefran       #+#    #+#             */
/*   Updated: 2020/11/16 11:54:22 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		print_error_args(void)
{
	ft_putstr_fd("Wrong arguments\n", STDERR_FILENO);
	return (FAILURE);
}

/*
** Returns SUCCESS if there is 4 or 5 arguments (last one is optional) and if
** they're all only made of digits.
*/
int		check_arguments(int ac, char **av)
{
	int		i;
	
	if (!(ac == 5 || ac == 6) && print_error_args())
		return (FAILURE);
	i = 1;
	while (i < ac)
		if (ft_strisdigit(av[i++]) && print_error_args())
			return (FAILURE);
	return (SUCCESS);
}

void	print_ms_and_state(char *str_ms, char *str_philo, char *str_msg)
{
	ft_putstr_fd(str_ms, 1);
	ft_putstr_fd("ms ", 1);
	ft_putstr_fd(str_philo, 1);
	ft_putstr_fd(str_msg, 1);
	free(str_ms);		//allocated in print_state_msg
	free(str_philo);	//allocated in print_state_msg
}

/*
** Prints a msg with : nb of ms since beginning, num_id of philosopher and the
** philosopher' state.
*/
int		print_state_msg(t_philo *ph, int id_philo, suseconds_t ms, int type)
{
	char	*str_ms;
	char	*str_philo;

	if (!(str_ms = ft_itoa(ms)))
		return (FAILURE);
	if (!(str_philo = ft_itoa(id_philo)))
	{
		free(str_ms);
		return (FAILURE);
	}
	pthread_mutex_lock(&(ph->mutex_num_philo));	//only one thread at a time can print
	if (type == EAT)
		print_ms_and_state(str_ms, str_philo, " is eating\n");
	else if (type == FORK)
		print_ms_and_state(str_ms, str_philo, " has taken a fork\n");
	else if (type == SLEEP)
		print_ms_and_state(str_ms, str_philo, " is sleeping\n");
	else if (type == THINK)
		print_ms_and_state(str_ms, str_philo, " is thinking\n");
	else if (type == DIE)
		print_ms_and_state(str_ms, str_philo, " has died\n");
	pthread_mutex_unlock(&(ph->mutex_num_philo));
	return (SUCCESS);
}

/*
** Returns the time in milliseconds.
*/
long	get_time_ms(void)
{
	struct timeval tmp_time;
	long			ms;

	gettimeofday(&tmp_time, NULL);
	ms = tmp_time.tv_sec * 1000;
	ms += tmp_time.tv_usec / 1000;
	return (ms);
}