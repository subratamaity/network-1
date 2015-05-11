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

#define MAXDATASIZE 100

int main(int argc,char *argv[])
{
	int sockfd,numbytes,try;
	char buf[MAXDATASIZE];
	struct hostent * he;
	struct sockaddr_in their_addr;
	printf("socket:");
	scanf("%d",&try);
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1){
		perror("socket");
		exit(1);
	}
	printf("connect:");
	scanf("%d",&try);
	their_addr.sin_family=AF_INET;
	their_addr.sin_port=htons(PORT);
	their_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(&(their_addr.sin_zero),'\0',8);

	if(connect(sockfd,(struct sockaddr *)&their_addr,
		sizeof(struct sockaddr))==-1){

		perror("connect");
		exit(1);
	}
	printf("send");
	scanf("%d",&try);
	//buf[numbytes]='\0';
	//recv(sockfd, buf, 1024, 0);
	//intf("Received: %s",buf);

	scanf("%s",buf);
	send(sockfd,buf,80,0);
	// getchar();
	
	printf("recv");
	scanf("%d",&try);

	recv(sockfd, buf, 80, 0);
	printf("%s\n",buf);

	printf("close");
	scanf("%d",&try);
	
	close(sockfd);
	return 0;
}
