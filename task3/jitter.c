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
#include <sys/time.h>

#define PORT 80

#define MAXDATASIZE 100

int main(int argc,char *argv[])
{
	int sockfd,numbytes,i,j;
	char reply[MAXDATASIZE];
	struct hostent * he;
	struct sockaddr_in their_addr;
	struct timeval t;
	struct timeval t1,t2;
	char *request="GET / HTTP/1.1\r\nHost: www.google.com\r\n\r\n";
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1){
		perror("socket");
		exit(1);
	}
	their_addr.sin_family=AF_INET;
	their_addr.sin_port=htons(PORT);
	their_addr.sin_addr.s_addr = inet_addr("173.194.36.82");
	memset(&(their_addr.sin_zero),'\0',8);

	if(connect(sockfd,(struct sockaddr *)&their_addr,
		sizeof(struct sockaddr))==-1){

		perror("connect");
		exit(1);
	}
	for(i=0;i<10000;i++){
		// send(sockfd,reply,4096,0);
		gettimeofday(&t1,NULL);
		send(sockfd,request, 4096, 0);
		// sendfile(new)
		recv(sockfd,reply,4096,0);
		printf("%s",reply);
		gettimeofday(&t2,NULL);
		printf("%d %lld\n",i,(long long int)(t2.tv_usec-t1.tv_usec));
	}
	// getchar();
	close(sockfd);

	return 0;
}
