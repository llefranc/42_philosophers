/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 21:08:56 by lucaslefran       #+#    #+#             */
/*   Updated: 2020/11/16 20:26:37 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

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
	pthread_mutex_lock(&(ph->ph_die->mutex));	//only one thread at a time can print
	if (!ph->ph_die->data && type == EAT)
		print_ms_and_state(id_philo, ms, " is eating\n");
	else if (!ph->ph_die->data && type == FORK)                   //if ph_die->data is set to 1, a philo
		print_ms_and_state(id_philo, ms, " has taken a fork\n");  //is dead : we don't print any messages
	else if (!ph->ph_die->data && type == SLEEP)                  //until program exit
		print_ms_and_state(id_philo, ms, " is sleeping\n");
	else if (!ph->ph_die->data && type == THINK)
		print_ms_and_state(id_philo, ms, " is thinking\n");
	else if (!ph->ph_die->data && type == DIE)
		print_ms_and_state(id_philo, ms, " has died\n");
	pthread_mutex_unlock(&(ph->ph_die->mutex));
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
