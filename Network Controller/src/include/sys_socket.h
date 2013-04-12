/**************************************************************************
*
* Copyright (C) 2012 hyc <heng@temcocontrols.com>
*
*function��send, sendmsg, recv, recvfrom, socket
*
*header files��#include <sys/types.h>   #include <sys/socket.h>
*
*function define: int sendto(int s, const void * msg, int len, unsigned int flags, const struct sockaddr * to, int tolen);
*
*����˵����
*sendto() ������������ָ����socket �����Է�����. 
*����s Ϊ�ѽ������ߵ�socket, �������UDPЭ�����辭�����߲���. 
*����msg ָ�������ߵ���������, 
*����flags һ����0, ��ϸ������ο�send(). 
*����to ����ָ�������͵������ַ, �ṹsockaddr ��ο�bind(). 
*����tolen Ϊsockaddr �Ľ������.

*����ֵ���ɹ��򷵻�ʵ�ʴ��ͳ�ȥ���ַ���, ʧ�ܷ��أ�1, ����ԭ�����errno ��.
 
*********************************************************************/



#ifndef SYSSOCKET_H
#define SYSSOCKET_H

#include <stdint.h>
#include <stdbool.h>


int sendto(int s, const void * msg, int len, unsigned int flags, const struct sockaddr * to, int tolen);




#endif