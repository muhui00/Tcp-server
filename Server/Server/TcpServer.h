#pragma once
#include "TcpSocket.h"

class TcpServer
{
public:
	TcpServer();
	~TcpServer();
	//���������ü���
	int setListen(unsigned short port);

	// �ȴ������ܿͻ�����������, Ĭ�����ӳ�ʱʱ��Ϊ10000s
	TcpSocket* acceptConnect(int timeout = 10000);

	//�Ͽ�����
	void closefd();
private:
	int m_lfd;
};