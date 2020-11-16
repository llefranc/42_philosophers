/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 13:01:47 by lucaslefran       #+#    #+#             */
/*   Updated: 2020/11/15 13:02:08 by lucaslefran      ###   ########.fr       */
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

char	*mallocstr(unsigned long temp, unsigned long *len)
{
	char *str;

	while (temp > 9)
	{
		temp /= 10;
		*len += 1;
	}
	if (!(str = malloc(sizeof(*str) * (*len + 1))))
		return (NULL);
	str[*len] = 0;
	*len -= 1;
	return (str);
}

char	*ft_itoa(long n)
{
	char			*str;
	unsigned long	temp;
	unsigned long	len;

	len = 1;
	temp = n;
	if (n < 0)
	{
		len++;
		temp = -n;
	}
	if (!(str = mallocstr(temp, &len)))
		return (NULL);
	if (n < 0)
		str[0] = '-';
	while (temp > 9)
	{
		str[len--] = (temp % 10) + 48;
		temp /= 10;
	}
	str[len] = temp + 48;
	return (str);
}
