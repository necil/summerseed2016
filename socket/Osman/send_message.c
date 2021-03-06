//#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h> 
#include <string.h> //for memset
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
//for struct sockaddr_in and socket parameters



#ifndef DEBUG
#define DEBUG 0
#endif

int main(int argc, char const *argv[])
{
	int sockfd = 0;
	char recvBuff[1024],sendBuff[1026];
	struct sockaddr_in serv_addr;
	char  mess[1024] ;
	int connfd,len=0;
	char *temp;
	//strcpy(mess,"172.16.5.187,Osman\t");

	/*------initiliaze timeout for socket ---------*/
	struct timeval timeout;      
	timeout.tv_sec = 0;
	timeout.tv_usec = 3;
	/*--------------------*/


	/*------create socket --------*/
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0))< 0){
		perror("Error create socket  ");
		return -1;
	}else if(DEBUG){
		printf("Socket create succes (receive message)\n");
	}



	/*------assign socket for timeout------*/
	setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,
	       (char *)&timeout, sizeof(timeout));

	/*------------server address  set ------*/
  	serv_addr.sin_family = AF_INET;
  	serv_addr.sin_port = htons(10002);
  	serv_addr.sin_addr.s_addr = inet_addr("172.16.5.187");


	
	printf("-----------------Send message ------------------\n");

	
		//if come a request to socket ,accept
		if((connfd=connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)))<0){
		  perror("Error connecting socket ");
		}else{
			printf("Accept socket\n");
		}
		

		printf("Please enter message>>");
		fgets (mess, 1024,stdin);
		//strncat(mess,"\t",strlen(mess)-2);
		strcpy(mess,strtok(mess,"\n"));
		strncat(mess,"\t",strlen(mess));
		printf("[%s] length : %d \n",mess ,(int)strlen(mess));

		//send message the socket
		printf("sent byte:%d\n",(int)write(sockfd,&mess,sizeof(mess)));
		printf("send message\n");
			
		/*-----close connection-----*/
		close(connfd);
//		close(sockfd);
		
	printf("Terminated connection\n");
	printf("-----------------END------------------\n\n");

	return 0;
}
