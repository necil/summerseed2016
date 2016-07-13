#include <stdio.h>
#include <stdlib.h>
#include <string.h>  
#include <unistd.h>  
#include <netdb.h>
#include <netinet/in.h>
#include <dirent.h>
#include "StringBuilder.h"

#ifndef MAXHOSTNAME
#define MAXHOSTNAME 256
#endif

void recv_msg(int port){
	
	int socketServer, socketClient, clientLen;
    struct sockaddr_in serverAddr, clientAddr;
	struct hostent *hp;
	char myname[MAXHOSTNAME+1], buf[1];
	StringBuilder str;
		
	 /* create socket */
    if((socketServer = socket(AF_INET , SOCK_STREAM , 0)) == -1){
        
		perror("Couldn't create a socket.");
		exit(1);
    }
    
    memset(&serverAddr, 0, sizeof(struct sockaddr_in));
    
	gethostname(myname, MAXHOSTNAME);
	
	if((hp = gethostbyname(myname)) == NULL){
		
		perror("Couldn't get hostname");
		close(socketServer);
		exit(1);
	}
	
	serverAddr.sin_family= hp->h_addrtype;
	serverAddr.sin_port= htons(port);
     
    /* bind */
    if(bind(socketServer, (struct sockaddr *)&serverAddr , sizeof(serverAddr)) == -1){
		
        perror("Couldn't bind socket");
		close(socketServer);
        exit(1);
    }
 
	listen(socketServer , 3);
	
	clientLen = sizeof(clientAddr);
			
	/* accept calls */
		
	if((socketClient = accept(socketServer, (struct sockaddr *)&clientAddr, (socklen_t *)&clientLen)) < 0){
	
		perror("Client couldn't accept");

		exit(1);
	}
	
	SBinitilize(&str);
	
	while(recv(socketClient, buf, 1, 0)){
		
		if(*buf == '\t')
			
			break;
			
		SBaddChar(&str, *buf);		
	}
		
	puts(str.str);
	
	close(socketServer);
	close(socketClient);
	SBclear(&str);
}