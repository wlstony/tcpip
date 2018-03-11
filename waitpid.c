#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
	int status;
	pid_t pid = fork();
	if(pid == 0){
		sleep(15);
		return 24;
	}else{
		//WNOHANG,没有终止的子进程也不会进入阻塞状态
		while(! waitpid(-1, &status, WNOHANG)){
			puts("sleep 3 sec.");
			sleep(3);
		}
		if(WIFEXITED(status)){
			printf("Child send %d \n", WEXITSTATUS(status));
		}
	}

	return 0;
}
