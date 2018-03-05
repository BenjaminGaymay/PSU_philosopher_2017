/*
** EPITECH PROJECT, 2018
** PSU_philosopher_2017
** File description:
** philo
*/

#include <ctype.h>
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
	t_philo philos = *(t_philo *)arg;
	
	// for (int i = 0; philos[i].nb_philos; i++) {
	// 	printf("%d\n", i);
	// }

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
		philos[i].nb_eat = 0;
		philos[i].status = REST;
	}
	for (int i = 0; i < info->nb_p; i++)
		if (pthread_create(&philos[i].thread, NULL, try, &philos[i]) != 0)
			return (ERROR);
	for (int i = 0; i < info->nb_p; i++)
		if (pthread_join(philos[i].thread, NULL) != 0)
			return (ERROR);
	return (SUCCESS);
}
