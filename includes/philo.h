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
#include <stdbool.h>

/*
** MACROS
*/
# define EXIT -1
# define ERROR 84
# define SUCCESS 0
# define FAILURE 1
# define NONE 0
# define LEFT 1
# define RIGHT 10
# define BOTH 11

/*
** STRUCTURES
*/
enum e_status {
	EAT,
	THINK,
	REST
};

typedef struct s_philo {
	pthread_mutex_t *right;
	pthread_mutex_t *left;
	enum e_status status;
	size_t nb_eat;
	pthread_t thread;
	int id;
	size_t nb_stick;
	bool l_stick;
	bool r_stick;
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
