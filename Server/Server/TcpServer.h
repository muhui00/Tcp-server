#pragma once
#include "TcpSocket.h"

class TcpServer
{
public:
	TcpServer();
	~TcpServer();
	//服务器设置监听
	int setListen(unsigned short port);

	// 等待并接受客户端连接请求, 默认连接超时时间为10000s
	TcpSocket* acceptConnect(int timeout = 10000);

	//断开连接
	void closefd();
private:
	int m_lfd;
};