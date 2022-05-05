#pragma once
#include <iostream>
#include <string.h>
#include "RequestCodec.h"
using namespace std;
//设计一个结构体来接收配置信息
struct clt_Info
{
	string clientID; //客户端id
	string serverID; //服务器id
	string serverIP; //服务器IP地址
	unsigned short serverPort;//服务器端口号
};
class ClientOP
{
public:
	ClientOP(string JsonFile);
	~ClientOP();
	//密钥协商
	bool keyAgreement();
	//密钥校验
	void keyVerification();
	//密钥注销
	void keyLogout();
private:
	clt_Info m_info;
};