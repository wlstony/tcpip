#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>

#define BUF_SIZE  1024
void error_handling(char *message);

int main(int argc, char *args[])
{
	int sock;
	struct sockaddr_in serv_addr;
	char message[BUF_SIZE];
	int str_len, recv_len=0;
	
	if(argc != 3) {
		printf("usage: %s <IP> <port>\n", args[0]);
		exit(1);
	}
	sock = socket(PF_INET, SOCK_STREAM, 0);
	if(sock == -1){
		error_handling("socket() error");
	}
	
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family= AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(args[1]);
	serv_addr.sin_port = htons(atoi(args[2]));
	
	if(connect(sock,(struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
		error_handling("connect() error!");
	else
		puts("Connected......");
	
	while(1){
		fputs("Input message(Q to quit): ", stdout);
		fgets(message, BUF_SIZE, stdin);
		if(! strcmp(message, "q\n")  || ! strcmp(message, "Q\n")){
			break;
		}
		str_len = write(sock, message, strlen(message));
		int recv_cnt = 0;
		recv_len = 0;
		while(recv_len < str_len){
			printf("read\n");
			recv_cnt =  read(sock, &message[recv_len], BUF_SIZE-1);
			if(recv_cnt == -1)
				error_handling("read() error");
			recv_len += recv_cnt;
		}
		
		
		printf("Message from server: %s\n", message);
	}
	
	
	close(sock);
	return 0;
}

void error_handling(char * message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
