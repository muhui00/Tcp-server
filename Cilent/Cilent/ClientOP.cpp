#include "ClientOP.h"
#include "CodecFactory.h"
#include "RequestFactory.h"
#include "RespondFactory.h"
#include "RequestCodec.h"
#include "RespondCodec.h"
#include "Hash.h"
#include "TcpSocket.h"
#include "RsaCrypto.h"
#include "Message.pb.h"
#include "AesCrypto.h"
#include <json/json.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string.h>
using namespace std;
using namespace Json;

ClientOP::ClientOP(string JsonFile) {
	//从配置文件读取数据初始化m_info
	ifstream ifs(JsonFile);
	Value root;
	Reader rd;
	rd.parse(ifs, root);
	m_info.serverID = root["ServerID"].asString();
	m_info.clientID = root["ClientID"].asString();
	m_info.serverIP = root["ServerIP"].asString();
	m_info.serverPort = root["Port"].asInt();
	//m_info.serverPort = 9898;
	
}

ClientOP::~ClientOP()
{}

bool ClientOP::keyAgreement()
{
	//准备RSA密钥对
	//创建RsaCrypto对象
	Cryptographic rsa;
	// 生成RSA密钥对
	rsa.generateRsakey(1024);
	//获取公钥(读公钥文件)
	ifstream ifs("public.pem");
	stringstream pubkeystr;
	pubkeystr << ifs.rdbuf();
	//初始化RequestInfo
	RequestInfo req_info;
	req_info.cmd = 1;
	req_info.clientID = m_info.clientID;
	req_info.serverID = m_info.serverID;
	req_info.data = pubkeystr.str();
	//加密公钥
	Hash hash(T_SHA1);
	hash.addData(pubkeystr.str());
	string datastr = hash.result();
	//公钥签名
	string strSign = rsa.rsaSign(datastr);
	req_info.sign = strSign;
	cout << "签名完成..." << endl;
	//序列化req_info 工厂类创建
	CodecFactory* factory = new RequestFactory(&req_info);
	Codec* codec = factory->createCodec();
	//得到序列化的数据，可以将其发给服务器
	string encstr = codec->encodeMsg();
	//释放资源
	delete factory;
	delete codec;
	//创建TcpSocket对象
	TcpSocket* tcp_sock = new TcpSocket;
	//连接服务器
	cout << "IP:" << m_info.serverIP << "  ,Port:" << m_info.serverPort << endl;
	int ret = tcp_sock->connectToHost(m_info.serverIP, m_info.serverPort);
	if (ret != 0) {
		cout << "server connect failed...." << endl;
		return false;
	}
	//连接成功，发送序列化数据
	tcp_sock->sendMsg(encstr);
	//等待服务器回复数据
	string recvmsg = tcp_sock->recvMsg();
	//解析服务器回复数据，反序列化
	//数据还原到RespondMsg
	factory = new RespondFactory(recvmsg);
	codec = factory->createCodec();
	RespondMsg*  resdata = (RespondMsg *)codec->decodeMsg();
	if (!resdata->status()) {
		cout << "keyAgreement error.." << endl;
		return false;
	}
	//将得到的密文解密
	string key = rsa.rsaPriKeyDecrypt(resdata->data());
	cout << "对称加密的秘钥: " << key << endl;

	delete factory;
	delete codec;
	delete tcp_sock;

	return true;
}
void ClientOP::keyLogout() {

}

void ClientOP::keyVerification() {

}