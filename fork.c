#include <stdio.h>
#include <unistd.h>

int gval = 0;
int main(int argc, char *argv[]) {
	pid_t pid;
	int lval = 20;
	gval++; lval += 5;

	printf("before fork: [gval=%d, lval=%d]\n", gval, lval);

	pid = fork();

	printf("after fork: [gval=%d, lval=%d]\n", gval, lval);

	if(pid == 0) {//pid 0, child process
		gval += 2, lval += 2;
	} else {
		gval -= 2, lval -= 2;
	}
	printf("pid: %d\n", pid);

	if(pid == 0){
		printf("Child proc: [gval=%d, lval=%d]\n", gval, lval);
	} else {
		printf("Parent proc: [gval=%d, lval=%d]\n", gval, lval);
	}

	return 0;
}
