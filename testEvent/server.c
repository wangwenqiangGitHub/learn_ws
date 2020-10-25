#include <stdio.h>
#include <stdlib.h>
#include <event.h>
#include <string.h>

#include <event2/listener.h>//宏
#include <event2/bufferevent.h>

#include <sys/types.h>          //socket
#include <sys/socket.h>

#include <netinet/in.h> //inet_addr
#include <arpa/inet.h>

//读取数据
void read_cb (struct bufferevent *bev, void *ctx)
{
    char buf[128] = {0};
    size_t ret = bufferevent_read(bev, buf, sizeof buf);
    int fd = *(int *)ctx;
    if(ret < 0)
    {
        printf("read null");
    }
    else
    {
        printf("read from %d %s\n",fd,buf);
    }
    
}
void event_cb (struct bufferevent *bev, short what, void *ctx)
{
    if(what & BEV_EVENT_EOF)
    {
        printf("客户端%d",*(int*)ctx);
        bufferevent_free(bev);//释放bufferevent对象
    }
}
void listener_cb (struct evconnlistener * listener, evutil_socket_t fd, 
                    struct sockaddr *addr, int socklen, void *arg)
{
    printf("fd %d\n",fd);
    struct event_base *base = arg;
    //针对已经存在socket创建bufferevent对象
    //事件集合（从主函数传递base）、fd（代表TCP连接）
    struct bufferevent *bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
    if(NULL == bev)
    {
        printf("error\n");
    }
    //给bufferevnt设置回调函数
    //bufferevent对象，读事件回调函数，写事件回调函数，其他事件回调函数，参数
    bufferevent_setcb(bev, read_cb, NULL, event_cb,(void *)&fd);
    //使能bufferevent
    bufferevent_enable(bev,EV_READ);
}
/*
socket 
bind
listen
accept
*/
int main(int argc, char ** argv)
{
    //创建一个事件集合
    struct event_base *base = event_base_new();
    if(base == NULL)
    {
        printf("erro\n");
    }
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof server_addr);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = 8000;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    //创建socket , bind , listen, accept, connection
    //创建监听对象，在指定的地址上监听接下来的TCP连接
    //事件集合，当有连接时候调用的函数，回调函数参数
   struct evconnlistener *listener =
    evconnlistener_new_bind(base, listener_cb, base,
    LEV_OPT_CLOSE_ON_FREE|LEV_OPT_REUSEABLE,10,(struct sockaddr*)&server_addr,sizeof server_addr) ;
    if(NULL == listener)
    {
        printf("evconnlistener_new_bind error\n");
        return 1;
    }

    //监听集合中的事件
    event_base_dispatch(base);

    //释放两个对象
    evconnlistener_free(listener);
    event_base_free(base);
    return 0;
}