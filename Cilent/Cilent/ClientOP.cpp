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
	//�������ļ���ȡ���ݳ�ʼ��m_info
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
	//׼��RSA��Կ��
	//����RsaCrypto����
	Cryptographic rsa;
	// ����RSA��Կ��
	rsa.generateRsakey(1024);
	//��ȡ��Կ(����Կ�ļ�)
	ifstream ifs("public.pem");
	stringstream pubkeystr;
	pubkeystr << ifs.rdbuf();
	//��ʼ��RequestInfo
	RequestInfo req_info;
	req_info.cmd = 1;
	req_info.clientID = m_info.clientID;
	req_info.serverID = m_info.serverID;
	req_info.data = pubkeystr.str();
	//���ܹ�Կ
	Hash hash(T_SHA1);
	hash.addData(pubkeystr.str());
	string datastr = hash.result();
	//��Կǩ��
	string strSign = rsa.rsaSign(datastr);
	req_info.sign = strSign;
	cout << "ǩ�����..." << endl;
	//���л�req_info �����ഴ��
	CodecFactory* factory = new RequestFactory(&req_info);
	Codec* codec = factory->createCodec();
	//�õ����л������ݣ����Խ��䷢��������
	string encstr = codec->encodeMsg();
	//�ͷ���Դ
	delete factory;
	delete codec;
	//����TcpSocket����
	TcpSocket* tcp_sock = new TcpSocket;
	//���ӷ�����
	cout << "IP:" << m_info.serverIP << "  ,Port:" << m_info.serverPort << endl;
	int ret = tcp_sock->connectToHost(m_info.serverIP, m_info.serverPort);
	if (ret != 0) {
		cout << "server connect failed...." << endl;
		return false;
	}
	//���ӳɹ����������л�����
	tcp_sock->sendMsg(encstr);
	//�ȴ��������ظ�����
	string recvmsg = tcp_sock->recvMsg();
	//�����������ظ����ݣ������л�
	//���ݻ�ԭ��RespondMsg
	factory = new RespondFactory(recvmsg);
	codec = factory->createCodec();
	RespondMsg*  resdata = (RespondMsg *)codec->decodeMsg();
	if (!resdata->status()) {
		cout << "keyAgreement error.." << endl;
		return false;
	}
	//���õ������Ľ���
	string key = rsa.rsaPriKeyDecrypt(resdata->data());
	cout << "�ԳƼ��ܵ���Կ: " << key << endl;

	delete factory;
	delete codec;
	delete tcp_sock;

	return true;
}
void ClientOP::keyLogout() {

}

void ClientOP::keyVerification() {

}