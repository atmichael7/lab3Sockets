#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
// Add header files

void error_handling(char *message);

int main(int argc, char* argv[])
{
	int sock;
	struct sockaddr_in serv_addr;
	char message[30];
	char from_server[30];
	int str_len;
	char send_msg[30];

	// Declarer variables
	
	if(argc!=3){
		printf("Usage : %s <IP> <port>\n", argv[0]);
		exit(1);
	}
	
	sock=socket(PF_INET, SOCK_STREAM, 0);
	if(sock == -1)
		error_handling("socket() error");
	
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
	serv_addr.sin_port=htons(atoi(argv[2]));
		
	if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr))==-1) 
		error_handling("connect() error!");
	
	while(1){

		/*
		str_len=read(sock, message, sizeof(message)-1);
		if(str_len==-1)
			error_handling("read() error!");
		
		printf("Message from server: %s \n", message); 
		*/

		printf("\nMessage to server: ");
		scanf("%s", message); // modify the message variable to store the outgoing message now
		//if (message == "quit")
		//	break;

		int i = 0;
		while (i <= sizeof message){
			send_msg[i] = message[i];
			i++;
		}

		printf("\n");


		send(sock, send_msg, sizeof(message)-1, 0); // send the message to the server

		//memset(message, 0, sizeof message); // clear messages

		recv(sock, from_server, sizeof(from_server)-1, 0); // wait for reply message from server
		//if (str_len(from_server) > 1)
			printf("Message from server: %s");
		// Implement the code
		// 1. Take input from the keyboard as a string
		// 2. Send the message from the keyboard
		// 3. Wait and receive a message from the connected server
		// 4. Print out the received message on the terminal
	}
	
	
	close(sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
