#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

pthread_mutex_t verrou = PTHREAD_MUTEX_INITIALIZER;

typedef struct arg_struct {
    int init;
    int end;
    int step;
    int *tab;
} arguments;

int getMax(int num1, int num2) {
    return (num1 > num2) ? num1 : num2;
}

void *findMaxInTab(arguments *tabArgs) {
    int *max;
    max = malloc( sizeof( int ) );

    pthread_mutex_lock (&verrou);
    for (int i = tabArgs->init; i <= tabArgs->end ; ++i) {
        *max = getMax(*max, tabArgs->tab[i]);
    }
    printf("init = %d, end = %d\n" , tabArgs->init, tabArgs->end);
    printf("max = %d\n" , *max);

    tabArgs->init += tabArgs->step;
    tabArgs->end += tabArgs->step;
    pthread_mutex_unlock (&verrou);
    pthread_exit(max);
}

int main() {
    int tab[20];
    srand(time(NULL));
    int n = 4;
    int maxFinal = INT_MIN;

    for (int i = 0; i < 20; ++i) {
        tab[i] = rand() % 1001;
        printf("%d\n", tab[i]);
    }

    int tabLen = (sizeof tab / sizeof tab[0]);
    int step = tabLen / n;
    int i = 0;

    pthread_t threads[n];
    void *maxPartial;

    arguments tabArgsInitials;
    tabArgsInitials.init = 0;
    tabArgsInitials.end = step -1;
    tabArgsInitials.step = step;
    tabArgsInitials.tab = tab;

    printf("tabLen = %d\n" , tabLen);
    for (int j = 0; j < n; ++j) {
        pthread_mutex_lock (&verrou);
        pthread_create(&threads[i], NULL, (void *(*)(void *)) findMaxInTab, (void *) &tabArgsInitials);
        i++;
        pthread_mutex_unlock (&verrou);
    }

    for (int x = 0; x < n; ++x) {
        pthread_join(threads[x], &maxPartial);
        maxFinal = getMax(maxFinal, *((int *) maxPartial));
    }

    printf("maxFinal : %d\n", maxFinal);
}
