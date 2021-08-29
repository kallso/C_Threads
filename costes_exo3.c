#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

void *routineThread(void *num) {
    int *value = (int *)num;
    printf("%d \n", *value);
    int newValue = (*value) * 2;
    printf("newvalue : %d \n", newValue);

    // ici je prévois un pointeur sur un entier et je réserve la place en mémoire pour retourner la valeur à retour[i] qui est un pointeur sans type.
    int *ret;
    ret = malloc( sizeof( int ) );
    *ret = newValue;
    pthread_exit(ret);
}

int main() {
    int n = 6;
    pthread_t num_thread[6];
    void *retours[6];

    for (int i = 0; i < n; i++) {
        pthread_create(&num_thread[i], NULL, routineThread, (void*) &i);
        pthread_join(num_thread[i], (void**)&(retours[i]));
    }

    for (int i = 0; i < n; i++) {
        printf("%d \n", *(int *)retours[i]);
    }
}
