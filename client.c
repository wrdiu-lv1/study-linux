#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

int main(){
        int c_fd;
        int n_read;
        char readBuf[128];
        char *msg = "msg from client";
        struct sockaddr_in c_addr;
        memset(&c_addr,0,sizeof(struct sockaddr_in));

        c_fd = socket(AF_INET,SOCK_STREAM,0);
        if(c_fd == -1){
                perror("socked");
                exit(-1);
        }

        c_addr.sin_family = AF_INET;
        c_addr.sin_port = htons(8989);
        inet_aton("192.168.56.104",&c_addr.sin_addr);
        if(connect(c_fd,(struct sockaddr *)&c_addr,sizeof(struct sockaddr_in)) == -1){
                perror("connect");
                exit(-1);
        }
        write(c_fd,msg,strlen(msg));

        n_read = read (c_fd,readBuf,128);
        if(n_read == -1){
                perror("read");
        }
        else{
                printf("get  message from server:%d ,%s\n",n_read,readBuf);
        }
        return 0;
}
