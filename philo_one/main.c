/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucaslefrancq <lucaslefrancq@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 21:06:40 by lucaslefran       #+#    #+#             */
/*   Updated: 2020/11/13 22:31:36 by lucaslefran      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		test;

void	*philo_life(void *ph)
{
	printf("test = %d\n", test++);
	return (ph);
}

pthread_t	*create_philos(int	nb_philos, t_philo *ph)
{
	pthread_t		*thread;
	int				i;

	i = 0;
	if (!(thread = malloc(sizeof(*thread) * (nb_philos))))
		return (NULL);
	while (i < nb_philos)
		pthread_create(&thread[i++], NULL, &philo_life, ph); //penser a checker le retour d'erreur ?
	return (thread);
}

pthread_mutex_t	*create_forks(int nb_forks)
{
	pthread_mutex_t	*mutex;
	int				i;

	i = 0;
	if (!(mutex = malloc(sizeof(*mutex) * (nb_forks))))
		return (NULL);
	while (i < nb_forks)
		pthread_mutex_init(&mutex[i++], NULL);
	return (mutex);
}

void	init_philo_struct(t_philo *ph, int ac, char **av)
{
	ph->nb_philo = ft_atoi(av[1]);
	ph->t_to_die = ft_atoi(av[2]);
	ph->t_to_eat = ft_atoi(av[3]);
	ph->t_to_sleep = ft_atoi(av[4]);
	ph->nb_each_philo_eat = ac == 6 ? ft_atoi(av[5]) : -1;
}

//penser a checker les retours d'erreurs
int		main(int ac, char **av)
{
	t_philo		ph;
	
	if (check_arguments(ac, av))
		return (FAILURE);
	init_philo_struct(&ph, ac, av);
	ph.thread = create_philos(ph.nb_philo, &ph);
	ph.mutex = create_forks(ph.nb_philo);
	return (0);
}