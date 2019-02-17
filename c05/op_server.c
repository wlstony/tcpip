#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 

#define BUF_SIZE 1024
#define OPSZ 4
void error_handling(char *message);
int caculate(int opnum, int opnds[], char operator);

int main(int argc, char *args[])
{
	int serv_sock, clnt_sock, i=0, str_len=0;
	char opinfo[BUF_SIZE];
	int result, opnd_cnt, recv_len=0;
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

		opnd_cnt = 0;
		read(clnt_sock, &opnd_cnt, 1);
		while((opnd_cnt * OPSZ + 1) > recv_len){
			str_len = read(clnt_sock, &opinfo[recv_len], BUF_SIZE);
			recv_len += str_len;
		}
		
		result = caculate(opnd_cnt, (int *)opinfo , opinfo[recv_len-1]);
		printf("result: %d\n", result);

		close(clnt_sock);
	}
	close(serv_sock);
}

int caculate(int opnum, int opnds[], char operator) {
    int ret = opnds[0], i;
	for(i=0; i<opnum; i++) {
		printf("opnum %d : %d\n", i, opnds[i]);
	}
	printf("operator: %c\n", operator);
    switch(operator){
        case '+':
			for(i=1; i<opnum; i++) ret += opnds[i];
            break;
        case '-':
			for(i=1; i<opnum; i++) ret -= opnds[i];
            break;
        case '*':
			for(i=1; i<opnum; i++) ret *= opnds[i];
            break;
    }
    return ret;
}
void error_handling(char * message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
