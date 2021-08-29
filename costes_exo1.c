#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int i;

void addition() {
    i = i + 10;
    printf("hello, thread fils %d\n", i);
    i = i + 20;
    printf("hello, thread fils %d\n", i);
}

int main() {
    pthread_t num_thread;
    i = 0;

    if (pthread_create(&num_thread, NULL, (void *(*)()) addition, NULL) != 0) {
        perror("pb pthread_create\n");
    }

    i = i + 1000;
    printf("hello, thread principal %d\n", i);

    i = i + 2000;
    printf("hello, thread principal %d\n", i);

    pthread_join(num_thread, NULL);
}


/*
 *
 * Le printf se fait en 2 ETAPES : d'abord evaluation de la chaine de char a afficher
 * PUIS l'affichage a l'ecran.
 * COmpte tenu des deux étapes on peut comprendre le deroulement de la sortie suivante :

hello, thread principal 1000      // le pthread_create prend du temps car la creation d'un thread est long (plus long de l'execution  des deux lignes suivantes)
                                   // donc on a l'addition, affectation puis affichage du thread principal qui s'affiche

hello, thread principal 3010      // Ensuite on a 3010 donc cela veut dire que l'on a continué dans le thread principal
                                  // puisqu'il y a eu l'addtion +2000 et affectation PUIS on est passé au thread secondaire
                                  // et le +10 a eu lieu ET on revient dans le tread principal est l'affichage du printf a lieu donc evaluation et affichage de i qui vaut a
                                  // ce moment la 3010.

hello, thread fils 1010          // Cette fois ci on revient dans le thread fils mais la valeur de i avait ete prealablement calculé dans la passe precedente,
                                // ca valeur étant a 1010 a ce moment c'est l'affichage qui avait ete mis en pause (la deuxieme etape du printf)
                                // le printf du fils affiche donc 1010

hello, thread fils 3030         // Cette fois ci on continue dans le thread fils mais avec acces a la valeur i mise a jours donc 3010, le thread fils ajoute 20
                                // puis affiche la nouvelle valeur 3030.

 */
