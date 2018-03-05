/*
** EPITECH PROJECT, 2018
** PSU_philosopher_2017
** File description:
** philo
*/

#include <ctype.h>
#include "extern.h"
#include "philo.h"

int is_numeric(const char *s)
{
	char *p;

	if (s == NULL || isspace(*s))
		return (0);
	strtod(s, &p);
	return (*p == '\0');
}

void *try(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	size_t nb_stick_bin = 0;

	while (philo->nb_eat != 0) {
		nb_stick_bin = 0;
		if (pthread_mutex_trylock(philo->left) == 0) {
			lphilo_take_chopstick(philo->left);
			nb_stick_bin += 1;
		}
		if (pthread_mutex_trylock(philo->right) == 0) {
			lphilo_take_chopstick(philo->right);
			nb_stick_bin += 10;
		}

		switch (nb_stick_bin) {
			case 0:
				lphilo_sleep();
				break;
			case 1:
				lphilo_think();
				pthread_mutex_unlock(philo->left);
				lphilo_release_chopstick(philo->left);
				break;
			case 10:
				lphilo_think();
				pthread_mutex_unlock(philo->right);
				lphilo_release_chopstick(philo->right);
				break;
			case 11:
				lphilo_eat();
				philo->nb_eat -= 1;
				pthread_mutex_unlock(philo->right);
				lphilo_release_chopstick(philo->right);
				pthread_mutex_unlock(philo->left);
				lphilo_release_chopstick(philo->left);
				break;
		}
	}
	pthread_exit(NULL);
}

int philo(t_info *info)
{
	t_philo philos[info->nb_p];
	pthread_mutex_t mutexs[info->nb_p];

	for (int i = 0 ; i < info->nb_p ; i++) {
		pthread_mutex_init(&mutexs[i], NULL);
		philos[i].left = &mutexs[i];
		philos[i].right = &mutexs[(i == 0 ? info->nb_p : i ) - 1];
		philos[i].nb_eat = info->nb_e;
		philos[i].status = REST;
		philos[i].id = i;
	}
	for (int i = 0; i < info->nb_p; i++)
		if (pthread_create(&philos[i].thread, NULL, try, &philos[i]) != 0)
			return (ERROR);
	for (int i = 0; i < info->nb_p; i++)
		if (pthread_join(philos[i].thread, NULL) != 0)
			return (ERROR);
	return (SUCCESS);
}
