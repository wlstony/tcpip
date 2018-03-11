#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>


void error_handling(char *message);

void ctrl_c(int sig){
	printf("ctrl_c");
	if(sig == SIGINT){
		printf("process exit\n");
		exit(1);
	}
}
int main(int argc, char *argv[]){
	int i;
	struct sigaction act;
	act.sa_handler = ctrl_c;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGINT, &act, 0);

	srand(time(NULL));
	while(1){
		i = rand();
		printf("rand number i:%d\n", i);
		sleep(1);
	}
	
	return 0;
}


void error_handling(char * message) {
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
