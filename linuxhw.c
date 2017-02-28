//
//  linuxhw.c
//  homework
//
//  Created by ma xiaoxiao on 16/12/11.
//  Copyright (c) 2016年 ma xiaoxiao. All rights reserved.
//

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#define smode 00751
char string []= "123";
main()
{
    int filedes[2],i,pid;
    char inbuf[256];
    char str[8]={0};
    int a=1;
    void createfile();
    
    
    
    if (pipe(filedes)<0)
    {
        perror("could not creat unnamed pipe");
        exit(1);
        
    }
    if((pid=fork())<0)
    {
        perror("could not create subprocess");
        exit(2);
    }
    if(pid>0)
    {
        sprintf(str,"file%d",a);
        close(filedes[0]);//close the pipe before write
        write(filedes[1],string,4);
        printf("the parent process sended\n");
        createfile();
        close(filedes[1]);//close the pipe after write
        //_mkdir("test");
        wait(0);
    }
    if(pid==0) //subprocess
    {
        memset(inbuf,0,sizeof(inbuf));
        close(filedes[1]);
        sleep(3);
        read(filedes[0],inbuf,23);
        printf("the subparent process received\n");
        printf("%s\n",inbuf);
        close(filedes[0]);
    }
    exit(0);
}
void createfile()
{
    int fd;
    if((fd = create("file1.txt",00751))== -1)
        perror("Can't create file file1.txt");
    else
        printf("create file1.txt successfully");
}

