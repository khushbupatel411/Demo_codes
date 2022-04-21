#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

void main()
{ char buff[100]="lseek is used to set offset";
char readfile[100];
int f1;
f1=open("filePointer.txt",O_CREAT|O_RDWR,777);
write(f1,buff,50);
lseek(f1,0,SEEK_SET);
read(f1,readfile,50);
printf("%s \n",readfile);
lseek(f1,-49,SEEK_CUR);
read(f1,readfile,50);
printf("%s \n",readfile);
lseek(f1,-25,SEEK_END);
read(f1,readfile,50);
printf("%s \n",readfile);

close(f1);
}

