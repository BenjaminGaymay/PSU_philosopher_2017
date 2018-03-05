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

int eat(t_philo *philo, size_t nb_stick_bin)
{
	lphilo_take_chopstick(philo->left);
	lphilo_take_chopstick(philo->right);
	lphilo_eat();
	lphilo_release_chopstick(philo->left);
	lphilo_release_chopstick(philo->right);
	philo->nb_eat -= 1;
	philo->status = REST;
}

int rest(t_philo *philo, size_t nb_stick_bin)
{
	philo->status = UNDEFINED;
}

int think(t_philo *philo, size_t nb_stick_bin)
{
	philo->status = THINK;
	switch (nb_stick_bin) {
		case LEFT:
			lphilo_take_chopstick(philo->left);
			lphilo_think();
			lphilo_release_chopstick(philo->left);
			return (0);
		case RIGHT:
			lphilo_take_chopstick(philo->right);
			lphilo_think();
			lphilo_release_chopstick(philo->right);
			return (0);
		case BOTH:
			return (eat(philo, nb_stick_bin));
		}
}

int (*actions[3])(t_philo *philo, size_t nb_stick_bin) =
{
	rest,
	think,
	eat
};

void *try(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	size_t nb_stick_bin = 0;

	while (philo->nb_eat != 0) {
		nb_stick_bin = 0;
		if (pthread_mutex_trylock(philo->left) == 0) {
			nb_stick_bin += LEFT;
		}
		if (pthread_mutex_trylock(philo->right) == 0) {
			nb_stick_bin += RIGHT;
		}
		if (philo->status == REST) {
			if (nb_stick_bin == LEFT or nb_stick_bin == RIGHT)
				think(philo, nb_stick_bin);
			else if (nb_stick_bin == BOTH)
				eat(philo, nb_stick_bin);
		}

		actions[philo->status](philo, nb_stick_bin);
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
		philos[i].status = UNDEFINED;
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
