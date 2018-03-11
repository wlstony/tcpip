#include <stdio.h>
#include <unistd.h>
#include <signal.h>

/*
SIGALARM 已经通过调用alarm函数注册的时间
SIGINT 输入CTRL+C
SIGCHLD 子进程终止
*/
void timeout(int sig) {
	if(sig == SIGALRM){
		puts("Time out!");
	}
	alarm(2);
}

void keycontrol(int sig){
	if(sig == SIGINT){
		puts("CTRL+C pressed");
	}
}

void childExit(int sig){
	puts("call childExit");
	if(sig == SIGCHLD){
		puts("child process exit");
	}
}

int main(int argc, char *argv[]){
	int i;
	signal(SIGALRM, timeout);
	signal(SIGINT, keycontrol);
	signal(SIGCHLD, childExit);
	alarm(2);

	pid_t pid = fork();
	if(pid == 0) {
		puts("child process sleep 3 seconds");
		sleep(3);
	}else{
		//发生信号时将唤醒由于调用sleep函数而进入阻塞状态的进程, 进程被唤醒, 不会再进入睡眠阻塞状态	
		for(i=0; i<3; i++){
			puts("wait...");
			sleep(100);
			puts("after wait...");
		}
	}

	return 0;
}
