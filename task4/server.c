#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

#define BUFSIZE 100

#define MYPORT 3490

#define BACKLOG 10

char res[BUFSIZE];
//Strrev returns the reverse of the string it takes
char *Strrev(char *str){
	int i,len;
	len=strlen(str);
	for(i=0;i<=len;i++){
		res[i]=str[len-i-1];
	}
	return res;
}
// void sigchld_handler(int s)
// {
	// while(wait(NULL)>0);
// }
int main(void){
	int sockfd,new_fd,try;
	struct sockaddr_in my_addr;
	struct sockaddr_in their_addr;
	int sin_size;
	struct sigaction sa;
	char buf[BUFSIZE];
	char buf1[BUFSIZE];
	int yes=1;
	printf("socket:");
	scanf("%d",&try);
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1){
		perror("socket");
		exit(1);
	}
	getchar();
	printf("bind:");
	scanf("%d",&try);
	getchar();
	my_addr.sin_family=AF_INET;
	my_addr.sin_port=htons(MYPORT);
	// The inet_addr() function converts the Internet
	// host address from the input from IPv4 
	// numbers-and-dots notation into binary data in 
	// network byte order
	my_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	//This fills a part of memory with a constant byte
	memset(&(my_addr.sin_zero),'\0',8);

	if(bind(sockfd,(struct sockaddr *)&my_addr,
		sizeof(struct sockaddr))==-1){
		perror("bind");
		exit(1);
	} 
	printf("listen:");
	scanf("%d",&try);
	if(listen(sockfd,40)==-1){
		perror("listen");
		exit(1);
	}
	printf("accept:");
	getchar();
	sin_size=sizeof(struct sockaddr);
	if((new_fd=accept(sockfd,(struct sockaddr *)&their_addr,&sin_size))==-1){
			perror("accept");
			exit(1);
	}
	//if(send(new_fd,"Hello, world!\n",1024,0)==-1)
	//			perror("send");
	// while(1){
	recv(new_fd, buf, 40, 0);
	printf("%s\n",buf);
	// }
	strcpy(buf1,Strrev(buf));
	printf("%s\n",buf1);
	if(send(new_fd,buf1,40,0)==-1)
				perror("send");
	printf("close new_fd:");
	scanf("%d",&try);
	close(new_fd);
	printf("close sockfd:");
	scanf("%d",&try);
	close(sockfd);
}