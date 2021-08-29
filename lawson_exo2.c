#include <stdio.h>
#include <pthread.h> 
#include <stdlib.h>

char *msg1, *msg2; 
pthread_t first_thread;
pthread_t second_thread;

void *msg(void *msgSent) {
	pthread_t id = pthread_self();
	if(pthread_equal(id, first_thread)) {
		fprintf(stdout, msgSent);
		pthread_exit("Je suis A et j'ai fini\n");
	} else {
		fprintf(stderr, msgSent);
		pthread_exit("Je suis B et j'ai fini\n");
	}
};

int main() { 


	msg1 = "msg1\n";
	msg2 = "msg2\n";
	void *threadReturnValue ;

	if (pthread_create(&first_thread, NULL, (void*) msg, (void*) msg1) != 0 || 			pthread_create(&second_thread, NULL, (void*) msg, (void*) msg2) != 0)
			perror ("pb pthread_create\n");
	
	pthread_join(first_thread, (void**) &threadReturnValue);
	printf("%s\n", threadReturnValue);
	pthread_join(second_thread, (void**) &threadReturnValue);
	fprintf(stderr, "%s\n", threadReturnValue);
}
