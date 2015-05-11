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
#include <sys/time.h>
#include <sys/stat.h>
#include <fcntl.h>
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
	int sockfd,new_fd,i,j;
	struct sockaddr_in my_addr;
	struct sockaddr_in their_addr;
	int sin_size;
	struct sigaction sa;
	char buf[BUFSIZE];
	char buf1[BUFSIZE];
	int yes=1;
	int fd;
	
	if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1){
		perror("socket");
		exit(1);
	}
	if(setsockopt(sockfd,SOL_SOCKET,
		SO_REUSEADDR,&yes,sizeof(int))==-1){
		perror("setsockopt");
		exit(1);
	}
	my_addr.sin_family=AF_INET;
	my_addr.sin_port=htons(MYPORT);
	// The inet_addr() function converts the Internet
	// host address from the input from IPv4 
	// numbers-and-dots notation into binary data in 
	// network byte order
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	//This fills a part of memory with a constant byte
	memset(&(my_addr.sin_zero),'\0',8);

	if(bind(sockfd,(struct sockaddr *)&my_addr,
		sizeof(struct sockaddr))==-1){
		perror("bind");
		exit(1);
	} 
	if(listen(sockfd,40)==-1){
		perror("listen");
		exit(1);
	}
	       sin_size = sizeof(struct sockaddr_in);
	       if ((new_fd = accept(sockfd, (struct sockaddr *)&their_addr,
	                                                      &sin_size)) == -1) {
	           perror("accept");
	           
		}	       
		printf("server: got connection from %s\n",
	                                          inet_ntoa(their_addr.sin_addr));
	for(i=0;i<1000;i++){
		// if((fd = open("in", O_RDWR))==-1){
			// perror("open");
		// }
		// send(new_fd,"hello world\n", 40, 0);		
		// if((sendfile(new_fd,fd,NULL,409666))==-1)
			// perror("sendfile");
		// if((close(fd))==-1){
			// perror("close");
			recv(sockfd,buf,4096,0);
			send(sockfd,"hi", 4096, 0);
		// sendfile(new)
	}
	// waitpid(0,NULL,0);
	// getchar();
	close(sockfd);
}