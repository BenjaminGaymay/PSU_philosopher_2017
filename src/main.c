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
	for (int i = 1 ; i < ac ; i++) {
		if ((strcmp(av[i], "--help") == 0 || strcmp(av[i], "-h") == 0))
			return (EXIT);
		else if (strcmp(av[i], "-e") == 0 && av[i + 1] && is_numeric(av[i + 1]))
			info->nb_e = atoi(av[i + 1]);
		else if (strcmp(av[i], "-p") == 0 && av[i + 1] && is_numeric(av[i + 1]))
			info->nb_p = atoi(av[i + 1]);
	}
	return (ac != 5 ? FAILURE : SUCCESS);
}

int main(int ac, char **av)
{
	t_info info;

	switch (get_info(&info, ac, av)) {
		case FAILURE:
			return (dispay_help(), ERROR);
		case EXIT:
			return (dispay_help(), SUCCESS);
	}

	RCFStartup(ac, av);
	philo(&info);
	printf("\n\n\n\n");
	RCFCleanup();
	return (SUCCESS);
}
