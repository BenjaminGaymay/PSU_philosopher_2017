/*
** EPITECH PROJECT, 2018
** PSU_philosopher_2017
** File description:
** philo
*/

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_lol {
	long long a;
	long long b;
	long long res;
} t_lol;

void *test_fc(void *arg)
{
	t_lol *mdr = arg;
	mdr->res = mdr->a + mdr->b;
	pthread_exit(mdr);
}

// int main(int ac, char **av)
// {
// 	size_t nb_arg = ac;
// 	t_lol a[nb_arg+1];

// 	for (size_t i = 1; i < nb_arg; i++) {
// 		a[i].a = atoll(av[i]);
// 		a[i].b = atoll(av[i]);
// 		a[i].res = 0;
// 	}
// 	pthread_t t[nb_arg+1];
// 	for (size_t i = 1; i < nb_arg; i++) {
// 		pthread_create(&t[i], NULL, test_fc, &a[i]);
// 	}
// 	t_lol *res = NULL;
// 	for (size_t i = 1; i < nb_arg; i++) {
// 		pthread_join(t[i], (void**)&res);
// 		printf("%lld\n", res->res);
// 		printf("thread n°%lu\n", t[i]);
// 	}
// 	return 0;
// }