#pragma once
#include <iostream>
#include <string.h>
#include "RequestCodec.h"
using namespace std;
//���һ���ṹ��������������Ϣ
struct clt_Info
{
	string clientID; //�ͻ���id
	string serverID; //������id
	string serverIP; //������IP��ַ
	unsigned short serverPort;//�������˿ں�
};
class ClientOP
{
public:
	ClientOP(string JsonFile);
	~ClientOP();
	//��ԿЭ��
	bool keyAgreement();
	//��ԿУ��
	void keyVerification();
	//��Կע��
	void keyLogout();
private:
	clt_Info m_info;
};