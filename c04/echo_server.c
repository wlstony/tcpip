#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 

#define BUF_SIZE 1024
void error_handling(char *message);

int main(int argc, char *args[])
{
	int serv_sock, clnt_sock, i=0, str_len=0;
	struct sockaddr_in serv_addr, clnt_addr;
	socklen_t clnt_addr_size;
	
	char message[BUF_SIZE];
	if(argc != 2){
		printf("usage : %s <port>\n",args[0]);
		exit(1);
	}
	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	if(serv_sock == -1)
		error_handling("socket() error");
	
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(atoi(args[1]));
	
	if(bind(serv_sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
		error_handling("bind() error");
	
	if(listen(serv_sock, 5) == -1)
		error_handling("listen() error");

	
	clnt_addr_size = sizeof(clnt_addr);
	for(i=0; i<5; i++){
		clnt_sock = accept(serv_sock,(struct sockaddr*)&clnt_addr, &clnt_addr_size);
		if(clnt_sock == -1)
			error_handling("accept() error");
		else
			printf("connected client %d\n", i+1);

		while((str_len = read(clnt_sock, message, BUF_SIZE)) != 0)
			write(clnt_sock, message, str_len);
		close(clnt_sock);
	}
	close(serv_sock);
}

void error_handling(char * message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
