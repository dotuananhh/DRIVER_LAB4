#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/ioctl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/select.h>
#include<sys/time.h>
#include<errno.h>
int main(int argc,char **argv){
    int file;
    int checkWrite,checkRead;
    file=open("/dev/lab4_2",O_RDWR);
    if (file<0)
    {
        printf( "Failed open file\n");
        exit(1);
    }
    printf("Open file successfully\n");
    checkWrite = write(file,&write,sizeof(write));
    if(checkWrite==1){
        printf( "Write successfully\n");
    }
    checkRead = read(file,&write,sizeof(write));
    if (checkRead==1)
    {
        printf( "Read successfully\n");
    }
}
