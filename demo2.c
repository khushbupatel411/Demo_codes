#include<pthread.h>
#include<stdio.h>
pthread_once_t once = PTHREAD_ONCE_INIT;
void *initfunction()
{
printf("\nThis is initialization function\n");
}
void *threadfunction(void *i)
{
printf("\nI am into thread = %d\n",(int *)i);
pthread_once(&once,(void *)initfunction);
printf("\n exit from mythread = %d\n",(int *)i);
}
int main()
{
	pthread_t thread;
	pthread_create(&thread,NULL,threadfunction,(void *)1);
	pthread_exit(NULL);
}





//code 2 :
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/types.h>
#include<bits/types.h>
static pthread_spinlock_t spinlock;
volatile int slock;
void *spinlockThread(void *i)
{
	int a;
printf("enter thread %d getting spin lock \n",(int *)i);
a = pthread_spin_lock(&slock);
printf("%d Thread unlock the spin lock\n",(int *)i);
a = pthread_spin_unlock(&slock);
printf("%d thread complete\n",(int *)i);
return NULL;
}	
int main()
{
	int a=0;
	int b=0;
	pthread_t  thread1,thread2;
	if(pthread_spin_init(&slock,PTHREAD_PROCESS_PRIVATE)!=0)
	perror("init");
	a = pthread_spin_lock(&slock);
	printf("spin lock created for thread 1..\n");
	a = pthread_create(&thread1 , NULL,spinlockThread , (int *)1);
	printf("thread 1 , now unlock the spin lock\n");
	a = pthread_spin_unlock(&slock);
	if(a==0)
{
	printf("\n  thread 1 successfully unlocked..\n");

}
else
{
	printf("\n thread1 unsuccessfully unlocked..\n");
}

printf("main, wait for the thread to end\n");
	b = pthread_spin_lock(&slock);
	printf("spin lock created for thread 2..\n");	
	b = pthread_create(&thread2 , NULL,spinlockThread , (int *)2);
	printf("thread 2 , now unlock the spin lock\n");
	b = pthread_spin_unlock(&slock);
	if(b==0)
{
	printf("\n  thread2 successfully unlocked..\n");
}
else
{
	printf("\n thread2 unsuccessfully unlocked..\n");
}
a = pthread_join(thread1,NULL);
b = pthread_join(thread2,NULL);
return 0;
}

