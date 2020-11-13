/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 21:08:56 by lucaslefran       #+#    #+#             */
/*   Updated: 2020/11/13 22:11:57 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int		ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

/*
** Return SUCCESS if the string is only made of digits, otherwise returns
** FAILURE.
*/
int		ft_strisdigit(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i++]))
			return (FAILURE);
	}
	return (SUCCESS);
}

long		ft_atoi(const char *str)
{
	long	nb;
	long	signe;
	long	i;

	nb = 0;
	signe = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
		signe *= -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return ((long)(nb * signe));
}

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