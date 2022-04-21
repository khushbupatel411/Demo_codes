//SERVER CODE :
#include <unistd.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <string.h>
 #include <netinet/in.h>
 #include<stdio.h>
 #include<stdlib.h>
 main(){
 int listfd,connfd,retval;
 //pid_t childpid;
 socklen_t clilen;
 struct sockaddr_in cliaddr, servaddr;
 listfd = socket(AF_INET, SOCK_STREAM, 0);//tep
 if (listfd<0)
{
 perror("sock:");
 exit(1);
}
 bzero(&servaddr, sizeof(servaddr));
 servaddr.sin_family = AF_INET;
 servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");//htonl(INADDR_ANY);
 servaddr.sin_port = htons(8000); //TCP protocol HTTP----port
 retval = bind(listfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
 if(retval < 0){
 perror("bind:");
 exit(2);
}
 listen(listfd, 5);
while(1)
{
	char buf[200];
	int n;
	clilen = sizeof(cliaddr);
	connfd=accept(listfd,(struct sockaddr *)&cliaddr , &clilen);
	printf("client connected....");
	n=read(connfd , buf,200);
	printf("\ndata received from client---");
	int m;
	for(m=n;m>=0;m--)
{
	buf[m];
	printf("%c\n",buf[m]);
}	//printf("\ndata rec from client = %s\n",buf);
	write(connfd , "\nGood Bye", 8);
}
}
//CLIENT CODE :
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdlib.h>
#include<netinet/in.h>
int main()
{
char buf[200];
char *serv_ip ="127.0.0.1";
int sockfd, ret_val;
int n;
struct sockaddr_in servaddr;
sockfd = socket(AF_INET, SOCK_STREAM, 0);
bzero(&servaddr, sizeof(servaddr));
servaddr.sin_family = AF_INET;
servaddr.sin_port = htons(8000);
inet_pton(AF_INET, serv_ip, &servaddr.sin_addr);
ret_val = connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
if(ret_val < 0)
{
perror("connect: ");
exit(1);
}
printf("ent the data.....\n");
gets(buf);
write(sockfd,buf,strlen(buf));
n=read(sockfd ,buf,200);
buf[n]='\0';
printf("rec d %s from server \n",buf);
close(sockfd);

}

