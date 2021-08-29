#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void routineThread1(char *message) {
    printf("%s", message);
    pthread_exit("Je suis A et j'ai fini\n");
}

void *routineThread2(char *message) {
    fprintf(stderr,"%s", message);
    return("Je suis B et j'ai fini\n");
}

int main() {
    char *message1 = "message initiale pour thread 1 \n";
    char *message2 = "message initiale pour thread 2 \n";

    pthread_t num_thread1;
    pthread_t num_thread2;

    if (pthread_create(&num_thread1, NULL, (void *(*)()) routineThread1, message1) != 0) {
        perror("pb pthread_create dans thread 1\n");
    }
    if (pthread_create(&num_thread2, NULL, (void *(*)()) routineThread2, message2) != 0) {
        perror("pb pthread_create dans thread 2\n");
    }
    void *retourTh2;
    void *retourTh1;

    pthread_join(num_thread2, &retourTh2);
    printf("%s", (char *) retourTh2);

    pthread_join(num_thread1, &retourTh1);
    fprintf(stderr,"%s", (char *) retourTh1);
}
