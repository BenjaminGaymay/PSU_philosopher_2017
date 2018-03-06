/*
** EPITECH PROJECT, 2018
** PSU_philosopher_2017
** File description:
** philo
*/

#include <unistd.h>
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

void eat(t_philo *philo)
{
	if (pthread_mutex_trylock(philo->left) && pthread_mutex_trylock(philo->right)) {
		lphilo_take_chopstick(philo->left);
		lphilo_take_chopstick(philo->right);
		lphilo_eat();
		philo->nb_eat--;
		philo->status = EAT;
		lphilo_release_chopstick(philo->left);
		lphilo_release_chopstick(philo->right);
		pthread_mutex_unlock(philo->left);
		pthread_mutex_unlock(philo->right);
	}
}

void rest(t_philo *philo)
{
	philo->status = REST;
	lphilo_sleep();
}

void try_think(t_philo *philo)
{
	if (pthread_mutex_trylock(philo->left) && philo->status != THINK)
		philo->l_stick = true;
	else if (pthread_mutex_trylock(philo->right) && philo->status != THINK)
		philo->r_stick = true;
}

void think(t_philo *philo)
{
	try_think(philo);
	if (philo->l_stick || philo->r_stick) {
		philo->status = THINK;
		lphilo_take_chopstick(philo->l_stick ? philo->left : philo->right);
		lphilo_think();
		lphilo_release_chopstick(philo->l_stick ? philo->left : philo->right);
		pthread_mutex_unlock(philo->l_stick ? philo->left : philo->right);
		philo->l_stick = false;
		philo->r_stick = false;
	}
}

void *try(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	while (philo->nb_eat != 0) {
		eat(philo);
		if (philo->status == EAT)
			rest(philo);
		if (philo->status == REST)
			think(philo);
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
		philos[i].nb_stick = NONE;
		philos[i].l_stick = false;
		philos[i].r_stick = false;
	}
	for (int i = 0; i < info->nb_p; i++) {
		if (pthread_create(&philos[i].thread, NULL, try, &philos[i]) != 0)
			return (ERROR);
	}
	for (int i = 0; i < info->nb_p; i++)
		if (pthread_join(philos[i].thread, NULL) != 0)
			return (ERROR);
	return (SUCCESS);
}
