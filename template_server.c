#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
// Add header files
#include <ctype.h>

void error_handling(char *message);

int main(int argc, char *argv[])
{
	int serv_sock;
	int clnt_sock;

	char convert[30];
	char ch;

	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;
	socklen_t clnt_addr_size;

	// Declarer variables

	char message[30];
	
	if(argc!=2){
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}
	
	serv_sock=socket(PF_INET, SOCK_STREAM, 0);
	if(serv_sock == -1)
		error_handling("socket() error");
	
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_addr.sin_port=htons(atoi(argv[1]));
	
	if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr))==-1 )
		error_handling("bind() error"); 
	
	if(listen(serv_sock, 5)==-1)
		error_handling("listen() error");
	
	clnt_addr_size=sizeof(clnt_addr);  
	clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_addr,&clnt_addr_size);
	if(clnt_sock==-1)
		error_handling("accept() error");  
	
	while(1){
		// write(clnt_sock, message, sizeof(message));
		// Implement code
		/*
		int x = 0;
		while (x <= 30){
			convert[x] = ' ';
			message[x] = ' ';
			x++;
		}
		*/
		
		read(clnt_sock, message, sizeof(message)-1);

		int i = 0;
		while (message[i] != NULL){
			ch = message[i];
			convert[i] = putchar(toupper(ch));
			i++;
		}

		send(clnt_sock, convert, sizeof(message)-1, 0); // send message to client
		
		
		// 1. Received messages from the connected client
		// 2. Change all lower case letters to their upper cases
		// 3. Return the modified data back to the client
	}
	
	close(clnt_sock);	
	close(serv_sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
