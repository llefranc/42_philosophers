/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 21:08:56 by lucaslefran       #+#    #+#             */
/*   Updated: 2020/11/18 13:32:43 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

/*
** Prints an error message on STDERR and returns FAILURE.
*/
int		error_msg(char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
	return (FAILURE);
}

/*
** Returns SUCCESS if there is 4 or 5 arguments (last one is optional) and if
** they're all only made of digits.
*/
int		check_arguments(int ac, char **av)
{
	int		i;
	
	if (!(ac == 5 || ac == 6))
		return (error_msg("Wrong arguments\n"));
	i = 1;
	while (i < ac)
		if (ft_strisdigit(av[i++]))
			return (error_msg("Wrong arguments\n"));
	if (ft_atoi(av[1]) > 1000 || ft_strlen(av[1]) > 4) //protecting arguments
		return (error_msg("Max nb of philosophers : 1000\n"));
	if (ft_atoi(av[2]) > 1000000 || ft_strlen(av[2]) > 7
			|| ft_atoi(av[3]) > 1000000 || ft_strlen(av[3]) > 7
			|| ft_atoi(av[4]) > 1000000 || ft_strlen(av[4]) > 7)
		return (error_msg("Max time in ms for args 2/3/4 : 1000000ms\n"));
	if (av[5] && (ft_atoi(av[5]) > 1000000 || ft_strlen(av[5]) > 7))
		return (error_msg("Max nb of time philo can eat : 1000000"));
	if (!ft_atoi(av[2]) || !ft_atoi(av[3]) || !ft_atoi(av[4]) || (av[5] && !ft_atoi(av[5])))
		return (error_msg("Arguments must be positive and > 0\n"));
	return (SUCCESS);
}

int		print_ms_and_state(int id, int ms, char *str_msg)
{
	int		len_id;
	int		len_ms;
	char	*tmp;

	len_id = lennb_for_str(id);
	len_ms = lennb_for_str(ms);
	if (!(tmp = malloc(len_id + len_ms + ft_strlen(str_msg) + 3 + 1))) //+3 for "ms "
		return (error_msg("Malloc failed\n"));
	tmp[len_id + len_ms + ft_strlen(str_msg) + 3] = '\0';
	ft_putnbr_buffer(ms, tmp);
	ft_strlcpy(tmp + len_ms, "ms ", 4);
	ft_putnbr_buffer(id, tmp + len_ms + 3);
	ft_strlcpy(tmp + len_id + len_ms + 3, str_msg, ft_strlen(str_msg) + 1);
	ft_putstr_fd(tmp, 1);
	free(tmp);
	return (SUCCESS);
}

/*
** Prints a msg with : nb of ms since beginning, num_id of philosopher and the
** philosopher' state.
*/
int		print_state_msg(t_philo *ph, int id_philo, suseconds_t ms, int type)
{
	sem_wait(ph->printing);
	if (type == EAT)
		print_ms_and_state(id_philo, ms, " is eating\n");
	else if (type == FORK)
		print_ms_and_state(id_philo, ms, " has taken a fork\n");
	else if (type == SLEEP)
		print_ms_and_state(id_philo, ms, " is sleeping\n");
	else if (type == THINK)
		print_ms_and_state(id_philo, ms, " is thinking\n");
	else if (type == DIE)
		print_ms_and_state(id_philo, ms, " has died\n");
	sem_post(ph->printing);
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
