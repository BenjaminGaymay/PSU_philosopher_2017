/*
** EPITECH PROJECT, 2018
** PSU_philosopher_2017
** File description:
** philo
*/

#include <unistd.h>
#include "extern.h"
#include "philo.h"

void eat(t_philo *philo)
{
	if (pthread_mutex_trylock(philo->left) &&
	pthread_mutex_trylock(philo->right)) {
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

void try_take(t_philo *philo)
{
	if (pthread_mutex_trylock(philo->left) && philo->status != THINK)
		philo->l_stick = true;
	else if (pthread_mutex_trylock(philo->right) &&
		philo->status != THINK)
		philo->r_stick = true;
}

void think(t_philo *philo)
{
	pthread_mutex_t *tmp = NULL;

	try_take(philo);
	if (philo->l_stick || philo->r_stick) {
		tmp = philo->l_stick ? philo->left : philo->right;
		philo->status = THINK;
		lphilo_take_chopstick(tmp);
		lphilo_think();
		lphilo_release_chopstick(tmp);
		pthread_mutex_unlock(tmp);
		philo->l_stick = false;
		philo->r_stick = false;
	}
}

void *try(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	while (philo->nb_eat != 0) {
		if (philo->status == THINK || philo->status == REST)
			eat(philo);
		if (philo->status == EAT) {
			philo->status = REST;
			lphilo_sleep();
		}
		else if (philo->status == REST)
			think(philo);
	}
	pthread_exit(NULL);
}

int philo(t_info *info)
{
	t_philo phis[info->nb_p];
	pthread_mutex_t mutexs[info->nb_p];

	for (int i = 0 ; i < info->nb_p ; i++) {
		pthread_mutex_init(&mutexs[i], NULL);
		phis[i].left = &mutexs[i];
		phis[i].right = &mutexs[(i == 0 ? info->nb_p : i ) - 1];
		phis[i].nb_eat = info->nb_e;
		phis[i].status = REST;
		phis[i].l_stick = false;
		phis[i].r_stick = false;
	}
	for (int i = 0; i < info->nb_p; i++)
		if (pthread_create(&phis[i].thd, NULL, try, &phis[i]) != 0)
			return (ERROR);
	for (int i = 0; i < info->nb_p; i++)
		if (pthread_join(phis[i].thd, NULL) != 0)
			return (ERROR);
	return (SUCCESS);
}
