#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/msg.h>
typedef struct 
{
	long msgtype;
	char buffer[100];
}msg;

main()
{
	int qid;
	int i;
	msg m1,m2;
	qid=msgget(32,IPC_CREAT|0644);
	m1.msgtype=10;
	for(i=0;i<10;i++)
{
	m1.buffer[i]='E';
	m2.msgtype=20;
}

	for(i=0;i<10;i++)
{
	m2.buffer[i]='I';
	//m2.msgtype=20;
}
	i=msgsnd(qid,&m1,sizeof(msg),0);
	printf("Return value of message send = %d ",i);
	i=msgsnd(qid,&m2,sizeof(msg),0);
	printf("Return value of message send = %d ",i);
	i=msgrcv(qid,&m1,sizeof(msg),10,0);
printf("\n...RECEIVED MSG LOOKS LIKE...\n");
	for(i=0;i<10;i++)
{
	printf("%c ",m1.buffer[i]);

}

	printf("\nmsg rec == %d\n",i);
	printf("\n");
	i=msgrcv(qid,&m2,sizeof(msg),20,0);
	for(i=0;i<10;i++)
{
	printf("%c ",m2.buffer[i]);


}
	//printf("\nmsg rec == %d\n",i);
	struct msqid_ds buf;
	qid=msgget(32,IPC_CREAT | 0644);
	printf("\nQUEUE ID = %d\n",qid);
	msgctl(qid,IPC_STAT,&buf);
	printf("\n...STRUCTURE OF MSG QUEUE...\n");
	printf("Number of msg in queue...%hi\n",buf.msg_qnum);
	printf("Maximum number of bytes in queue..%hi\n",buf.msg_qbytes);

qid=msgget(49,IPC_CREAT|0644);
	//printf("qid = %d\n",qid);
	msgctl(qid,IPC_RMID,NULL);

	printf("\n...MESSAGE REMOVED...\n");

	
}

