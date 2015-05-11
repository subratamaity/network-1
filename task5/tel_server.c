#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFSIZE 100

#define MYPORT 3490

#define BACKLOG 10

int main(void){
	int sockfd,new_fd,fd,ret;
	struct sockaddr_in my_addr;
	struct sockaddr_in their_addr;
	int sin_size;
	char buf[BUFSIZE],buf1[BUFSIZE];
	int len;
	int yes=1;
	int i,j;
	char redirect[]=">out";
	char *end0="echo '\0' >> out";
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
	my_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
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
	if((new_fd=accept(sockfd,(struct sockaddr *)&their_addr,&sin_size))==-1){
			perror("accept");
			exit(1);
	}
	//if(send(new_fd,"Hello, world!\n",1024,0)==-1)
	//			perror("send");
	// while(1){
	for(;;){
		if(recv(new_fd, buf, 40, 0)==-1)
			perror("recv : ");
		// printf("%s\n",buf);
		len=strlen(buf);
		for(i=len,j=0;redirect[j]!='\0';i++,j++){
			buf[i]=redirect[j];
		}
		buf[i]='\0';
		ret=system(buf);
		//system(end0);
		// }
		//getchar();
		if(ret==-1){
			send(new_fd,"command not found:",40,0);
		}
		else{
			fd=open("out",O_RDONLY);
			if(fd==-1) send(new_fd,"server error:",40,0); 
			printf("no of bytes sent %d",sendfile(new_fd,fd,0,4096));
		}
	//if(send(new_fd,buf1,40,0)==-1)
	//			perror("send");
	}
	getchar();
	close(new_fd);
	close(sockfd);
}