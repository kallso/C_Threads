#include <stdio.h>
#include <pthread.h> 
#include <stdlib.h>

void *threadRoutine(void *index) {

	printf("routine : %d\n", *(int *) index);

	//int res = (*(int *) index) * 2;
	int *res = malloc(sizeof(int));
	*res = ((*(int *) index) * 2);
	pthread_exit(res);
};

int main() { 

	void *threadReturnValue ;
	int n = 3;
	pthread_t threads[n];

	for (int i=1; i<=n; i++){
		printf("%d\n", i);
		pthread_create(&threads[i], NULL, threadRoutine, (void*) &i);

		// pthread_join(threads[i], &threadReturnValue);
		//printf("resulat : %d\n", *(int *) threadReturnValue);
	}

	for (int i=1; i<=n; i++){
		pthread_join(threads[i], &threadReturnValue);
		printf("resulat : %d\n", *(int *) threadReturnValue);
	}

}
