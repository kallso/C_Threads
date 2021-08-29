#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <setjmp.h>

int main( )
{
    /*printf("Hello, World!\n");
    return 0;*/

    /*unsigned int seconds = 15;
    int retour = alarm(seconds);
    sleep(3);
    int retour2 = alarm(5);
    printf("%d", retour);
    printf("%d", retour2);*/

    alarm(3);
    pause();

    sigpending();
    sigsuspend();
    setjmp();
    sigaction();
    sigemptyset(48);

    //onalarm();
    /*unsigned retour = sleep(15);
    printf("%d", retour);*/

    /*signal();
    sigaction();*/
}
