/*
** EPITECH PROJECT, 2018
** PSU_philosopher_2017
** File description:
** main
*/

#include "philo.h"
#include "extern.h"

void dispay_help()
{
	printf("USAGE\n\t./philo -p nbr_p -e nbr_e\n\nDESCRIPTION");
	printf("\n\t-p nbr_p number of philosophers\n\t-e nbr_e maximum num");
	printf("ber times a philosopher eats before exiting the program\n");
}

int get_info(t_info *info, int ac, char **av)
{
	if (ac != 3 || is_numeric(av[1]) == 0 || is_numeric(av[2]) == 0)
		return (FAILURE);
	info->nb_p = atoi(av[1]);
	info->nb_e = atoi(av[2]);
	return (SUCCESS);
}

int main(int ac, char **av)
{
	t_info info;

	if (ac == 1)
		return (ERROR);
	if ((strcmp(av[1], "--help") == 0 || strcmp(av[1], "-h") == 0))
		return (dispay_help(), SUCCESS);
	if (get_info(&info, ac, av) == FAILURE)
		return (dispay_help(), ERROR);
	RCFStartup(ac, av);
	philo(&info);
	RCFCleanup();
	return (SUCCESS);
}