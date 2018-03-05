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


int philo(t_info *info)
{
	t_philo mdr[info->nb_p];
	return (SUCCESS);
}