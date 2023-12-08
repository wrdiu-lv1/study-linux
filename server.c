#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
//#include <linux/in.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main()
{
        int s_fd;//表示socket的文件描述符
        int n_read;//读取的字节数
        char readBuf[128];//定义一个数组存储从客户端读取的数据的缓冲区

        char *msg = "I got your message";//要发送的信息
        struct sockaddr_in s_addr;//服务器的地址
        struct sockaddr_in c_addr;//客户端的地址
        memset(&s_addr,0,sizeof(struct sockaddr_in)); //一般来说先清空空间数据，再配置。避免结构体里面有杂乱数据
        memset(&c_addr,0,sizeof(struct sockaddr_in));

        //1.socket
        s_fd = socket(AF_INET,SOCK_STREAM,0);//创建一个TCP socket
        //创建失败
        if(s_fd == -1){
                perror("socked");
                exit(-1);
        }

        s_addr.sin_family = AF_INET;//服务器的地址
        s_addr.sin_port = htons(8989);//端口号
        inet_aton("192.168.56.104",&s_addr.sin_addr);  //主机地址转换为二进制格式

        //2.bind 绑定
        bind(s_fd, (struct sockaddr *)&s_addr,sizeof(struct sockaddr_in));

        //3.listen 监听socket，最大连接数为10
        listen(s_fd,10);

        //4.accept 接受来自客户端的连接
	int clen = sizeof(struct sockaddr_in);//长度 定义存储客户端地址的结构体的大小
        int c_fd = accept(s_fd,(struct sockaddr *)&c_addr, &clen);

        if(c_fd == -1){
                perror("accept");
        }
        //成功则打印客户端ip地址
        printf("get connect:%s\n",inet_ntoa(c_addr.sin_addr));    //inet_ntoa()函数，把网络格式的 IP 地址转为字符串形式

//服务端与客户端之间数据交互

        //5.read
        n_read = read(c_fd,readBuf,128);//把客户端的内容读到readBuf

        if(n_read == -1){
                perror("read");
        }else{
                printf("get message: %d,%s\n",n_read,readBuf);//打印readBuf中内容
        }

        //6.write
        write(c_fd,msg,strlen(msg));//写入操作

        return 0;
}
