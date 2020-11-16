/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 13:01:47 by lucaslefran       #+#    #+#             */
/*   Updated: 2020/11/16 20:25:20 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

/*
** Writes string *s on a specific fd.
*/
void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

/*
** Returns the len of string *s.
*/
size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

/*
** Returns 1 if c is a digit, 0 otherwise.
*/
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

/*
** Transforms string *str into an int. Returns 0 is *str is not a number.
*/
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

/*
** More opti than usleep function.
*/
void	sleep_better(long nb_ms)
{
	long		time;

	time = get_time_ms();
	while (get_time_ms() - time < nb_ms)
		continue ;
}

int		lennb_for_str(unsigned int nb)
{
	int len;

	len = 1;
	while (nb > 9)
	{
		len++;
		nb /= 10;
	}
	return (len);
}

int		lennb(unsigned int nb)
{
	int len;

	len = 1;
	while (nb > 9)
	{
		len *= 10;
		nb /= 10;
	}
	return (len);
}

void	ft_putnbr_buffer(int n, char *str)
{
	unsigned int	temp;
	unsigned int	len;
	char			carac;

	carac = '-';
	temp = n;
	if (n < 0)
	{
		*str = carac;
		str++;
		temp = -n;
	}
	len = lennb(temp);
	while (len >= 10)
	{
		*str = temp / len + 48;
		str++;
		temp %= len;
		len /= 10;
	}
	*str = temp + 48;
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t i;
	size_t len;

	i = 0;
	len = 0;
	if (src == NULL)
		return (0);
	while (src[len])
		len++;
	if (dstsize == 0)
		return (len);
	while (i < (dstsize - 1) && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (len);
}
