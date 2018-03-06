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

size_t get_stick(t_philo *philo)
{
	size_t nb = NONE;

	if (pthread_mutex_trylock(philo->left) == 0) {
		printf("%d GET LEFT\n", philo->id);
		nb += LEFT;
	}
	if (pthread_mutex_trylock(philo->right) == 0) {
		printf("%d GET RIGHT\n", philo->id);
		nb += RIGHT;
	}
	philo->nb_stick = nb;
	return (nb);
}

void rest(t_philo *philo)
{
	size_t nb_stick = get_stick(philo);

	lphilo_sleep();
	printf("REST %d : je dors\n", philo->id);
	if (nb_stick == LEFT || nb_stick == RIGHT) {
		philo->status = THINK;
		printf("REST %d : je vais THINK\n", philo->id);
	}
	else if (nb_stick == BOTH) {
		philo->status = EAT;
		printf("REST %d : je vais EAT\n", philo->id);
	}
}

void think(t_philo *philo)
{
	if (philo->nb_stick == LEFT) {
		printf("THINK %d : je prend LEFT\n", philo->id);
		lphilo_take_chopstick(philo->left);
		philo->l_stick = true;
	}
	else {
		printf("THINK %d : je prend RIGHT\n", philo->id);
		lphilo_take_chopstick(philo->right);
		philo->r_stick = true;
	}
	printf("THINK %d : je pense\n", philo->id);
	lphilo_think();
	usleep(500);
	while (get_stick(philo) == NONE)
	{
		usleep(500);
		printf("THINK %d : je pense (boucle)\n", philo->id);
		lphilo_think();
	}
	printf("THINK %d : je vais EAT\n", philo->id);
	philo->status = EAT;
}

void eat(t_philo *philo)
{
	if (philo->l_stick) {
		printf("EAT %d : je prend RIGHT\n", philo->id);
		lphilo_take_chopstick(philo->right);
	}
	else if (philo->r_stick) {
		printf("EAT %d : je prend LEFT\n", philo->id);
		lphilo_take_chopstick(philo->left);
	}
	else {
		printf("EAT %d : je prend RIGHT et LEFT\n", philo->id);
		lphilo_take_chopstick(philo->left);
		lphilo_take_chopstick(philo->right);
	}
	printf("EAT %d : je mange\n", philo->id);
	lphilo_eat();
	usleep(1000);
	printf("EAT %d : je lache LEFT et RIGHT\n", philo->id);
	lphilo_release_chopstick(philo->left);
	pthread_mutex_unlock(philo->left);
	lphilo_release_chopstick(philo->right);
	pthread_mutex_unlock(philo->right);
	philo->l_stick = false;
	philo->r_stick = false;
	printf("EAT : je vais dormir\n");
	philo->status = REST;
	philo->nb_eat -= 1;
}

void (*actions[3])(t_philo *philo) =
{
	eat,
	think,
	rest
};

void *try(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	while (philo->nb_eat != 0) {
		get_stick(philo);
		if (philo->nb_stick == BOTH)
			eat(philo);
		else if (philo->nb_stick == LEFT || philo->nb_stick == RIGHT) {
			think(philo);
			eat(philo);
		}
		lphilo_sleep();
		// actions[philo->status](philo);
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
		usleep(1000);
	}
	for (int i = 0; i < info->nb_p; i++)
		if (pthread_join(philos[i].thread, NULL) != 0)
			return (ERROR);
	return (SUCCESS);
}
