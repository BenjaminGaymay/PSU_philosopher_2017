/*
** EPITECH PROJECT, 2018
** PSU_philosopher_2017
** File description:
** main
*/

#include <string.h>
#include <stdio.h>
#include "philo.h"

void dispay_help()
{
	printf("USAGE\n\t./philo -p nbr_p -e nbr_e\n\nDESCRIPTION");
	printf("\n\t-p nbr_p number of philosophers\n\t-e nbr_e maximum num");
	printf("ber times a philosopher eats before exiting the program\n");
}

int main(int ac, char **av)
{
	if (ac == 1)
		return (ERROR);
	if ((strcmp(av[1], "--help") == 0 || strcmp(av[1], "-h") == 0))
		return (dispay_help(), SUCCESS);
	return (SUCCESS);
}