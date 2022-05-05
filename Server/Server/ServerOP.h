#pragma once
#include <iostream>
#include <string.h>
#include "TcpServer.h"
#include "TcpSocket.h"
#include "Message.pb.h"
#include <map>
using namespace std;
struct svr_info
{
	string serverID;
	unsigned short port;
};
class ServerOP
{
public:
	enum keylen
	{
		Len16 = 16,
		Len24 = 24,
		Len32 = 32
	};
	ServerOP(string configname);
	~ServerOP();
	//����������
	void satrtServer();
	//�ص�����
	static void* callback(void* arg);
	//��ԿЭ��
	string keyAgreement(RequestMsg* reqmsg);
private:
	//����ַ���
	string getRandStr(keylen len);
private:
	svr_info m_info;
	map<pthread_t, TcpSocket*>m_list;
	TcpServer* m_server = NULL;
};