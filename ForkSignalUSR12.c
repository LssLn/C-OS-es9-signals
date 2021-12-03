/*
	Due processi, padre e figlio, si scambiano segnali, utilizzando USR1 e USR2.
	Il padre alla ricezione del segnale USR1 dal figlio stampa "ping", il figlio alla ricezione del segnale USR2 dal 		padre stampa "pong".
*/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
//#include<sys/wait.h>
#include<unistd.h>
#include<signal.h>

void usr2handler(int sig){
    sleep(1);
	printf("\nChild : pong");
	sleep(1);
}

void usr1handler(int sig){
    sleep(1);
	printf("\nParent : ping");
	sleep(1);
}

int main(){
	pid_t pid;
	struct sigaction act;
	sigemptyset(&act.sa_mask);
	act.sa_flags=0;
	act.sa_handler=usr1handler;
	sigaction(SIGUSR1,act,NULL);
	act.sa_handler=usr2handler;
	sigaction(SIGUSR2,act,NULL);

	pid=fork();
	switch(pid){
		case 0:
			printf("Child sending USR1 to the parent\n");
			kill(getppid(),SIGUSR1);
			//sleep(1);
			//exit(EXIT_SUCCESS);
			break;
		default:
			printf("PArent sending USR2 to the child\n");
			kill(getpid(),SIGUSR2);
			//wait(&status);
			break;
	}
    sleep(1);
	exit(EXIT_SUCCESS);
}