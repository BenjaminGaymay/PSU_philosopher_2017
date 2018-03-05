/*
** EPITECH PROJECT, 2018
** PSU_philosopher_2017
** File description:
** pilo.
*/

#pragma once

#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

/*
** MACROS
*/
# define EXIT -1
# define ERROR 84
# define SUCCESS 0
# define FAILURE 1

/*
** STRUCTURES
*/
typedef struct s_philo {
	pthread_t thread;
	size_t rice;
	size_t status;
	size_t nb_eat;
} t_philo;

typedef struct s_info {
	int nb_p;
	int nb_e;
} t_info;

/*
** PROTOTYPES
*/
int philo(t_info *);
int is_numeric(const char *);
