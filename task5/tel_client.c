#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

#define PORT 3490

#define MAXDATASIZE 4096

int main(int argc,char *argv[])
{
	int sockfd,numbytes;
	char *buf=NULL,buf1[MAXDATASIZE];
	int i,j;
	struct hostent * he;
	struct sockaddr_in their_addr;
	size_t len=100;
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1){
		perror("socket");
		exit(1);
	}
	their_addr.sin_family=AF_INET;
	their_addr.sin_port=htons(PORT);
	their_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(&(their_addr.sin_zero),'\0',8);

	if(connect(sockfd,(struct sockaddr *)&their_addr,
		sizeof(struct sockaddr))==-1){

		perror("connect");
		exit(1);
	}

	//buf[numbytes]='\0';
	//recv(sockfd, buf, 1024, 0);
	//intf("Received: %s",buf);
	//scanf("%s",buf);
	for(j=0;;j++){
		printf("[ telnet ]$");
		getline(&buf,&len,stdin);
		for(i=0;buf[i]!='\n' ;i++)
			;
		buf[i]='\0';
		send(sockfd,buf,80,0);
		// getchar();
		recv(sockfd, buf1,4096, 0);
		for(i=0;buf1[i]!='\0';i++)
			printf("%c",buf1[i]);
		printf("\n");
	}
	getchar();
	close(sockfd);

	return 0;
}