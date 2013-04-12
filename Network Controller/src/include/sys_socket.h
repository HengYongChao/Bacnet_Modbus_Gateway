/**************************************************************************
*
* Copyright (C) 2012 hyc <heng@temcocontrols.com>
*
*function：send, sendmsg, recv, recvfrom, socket
*
*header files：#include <sys/types.h>   #include <sys/socket.h>
*
*function define: int sendto(int s, const void * msg, int len, unsigned int flags, const struct sockaddr * to, int tolen);
*
*函数说明：
*sendto() 用来将数据由指定的socket 传给对方主机. 
*参数s 为已建好连线的socket, 如果利用UDP协议则不需经过连线操作. 
*参数msg 指向欲连线的数据内容, 
*参数flags 一般设0, 详细描述请参考send(). 
*参数to 用来指定欲传送的网络地址, 结构sockaddr 请参考bind(). 
*参数tolen 为sockaddr 的结果长度.

*返回值：成功则返回实际传送出去的字符数, 失败返回－1, 错误原因存于errno 中.
 
*********************************************************************/



#ifndef SYSSOCKET_H
#define SYSSOCKET_H

#include <stdint.h>
#include <stdbool.h>


int sendto(int s, const void * msg, int len, unsigned int flags, const struct sockaddr * to, int tolen);




#endif