#include "ServerOP.h"
#include "TcpSocket.h"
#include "TcpServer.h"
#include "Message.pb.h"
#include "RespondCodec.h"
#include "RsaCrypto.h"
#include "Hash.h"
#include "AesCrypto.h"
#include "Codec.h"
#include "CodecFactory.h"
#include "RequestCodec.h"
#include "RespondCodec.h"
#include "RespondFactory.h"
#include "RequestFactory.h"
#include <json/json.h>
#include <string.h>
#include <fstream>
#include <unistd.h>
using namespace std;
using namespace Json;
ServerOP::ServerOP(string configname)
{
	//�������ļ���ȡ���ݳ�ʼ��
	Value root;
	ifstream ifs(configname);
	Reader rd;
	rd.parse(ifs, root);
	m_info.serverID = root["ServerID"].asString();
	m_info.port = root["Port"].asInt();
}

ServerOP::~ServerOP()
{
	if (m_server) {
		delete m_server;
	}
}

void ServerOP::satrtServer()
{
	//����TcpServer����
	//���ü���
	m_server = new TcpServer;
	m_server->setListen(m_info.port);
	while (1)
	{
		// �ȴ������ܿͻ�����������, Ĭ�����ӳ�ʱʱ��Ϊ10000s
		TcpSocket* tcp_sock = m_server->acceptConnect();
		if (tcp_sock == NULL) {
			//����ʧ��
			continue;
		}
		cout << "client connect success..." << endl;
		pthread_t tid = 0;
		pthread_create(&tid, NULL, callback, this);
		m_list.insert(make_pair(tid, tcp_sock));
	}

}

void* ServerOP::callback(void* arg)
{
	sleep(1);
	string data = string();
	// ͨ�����������ݵ�this����ת��
	ServerOP* op = (ServerOP*)arg;
	//pthread_self(),��ȡ�̱߳�����߳�id
	TcpSocket* tcp = op->m_list[pthread_self()];
	
	//�յ����ݣ����ݷ����л�������
	string msg = tcp->recvMsg();
	CodecFactory* factory = new RequestFactory(msg);
	Codec* codec = factory->createCodec();
	RequestMsg* req = (RequestMsg *)codec->decodeMsg();
	//����cmdType�жϿͻ�����Ҫ��ʲô
	switch (req->cmdtype())
	{
	case 1: //��ԿЭ��
		data = op->keyAgreement(req);
		break;
	case 2: //��ԿУ��
		break;
	case 3: 
		break;
	default:
		break;
	}
	//�ͷ���Դ
	delete factory;
	delete codec;
	//tcp������
	tcp->sendMsg(data);
	tcp->disConnect();
	//ɾ��
	op->m_list.erase(pthread_self());
	return NULL;
}

string ServerOP::keyAgreement(RequestMsg* reqmsg)
{
	// 0. ��ǩ������У�� -> ��Կ���� -> �õ���Կ
	// ���յ��Ĺ�Կ����д�뱾�ش���
	ofstream ofs("public.pem");
	ofs << reqmsg->data();
	ofs.close();
	RespondInfo res_info;
	// �����ǶԳƼ��ܶ���
	Cryptographic rsa("public.pem", false);
	// ������ϣ����
	Hash hash(T_SHA1);
	hash.addData(reqmsg->data());
	//У��ǩ��
	cout << "1111111111111111111111" << endl;
	bool b1 = rsa.rsaVerify(hash.result(), reqmsg->sign());
	cout << "0000000000000000000000" << endl;
	if (b1 == false) {
		cout << "ǩ��У��ʧ��..." << endl;
		res_info.status = false;
	}
	else
	{
		cout << "ǩ��У��ɹ�...." << endl;
		// 1. ��������ַ���
		// �ԳƼ��ܵ���Կ, ʹ�öԳƼ����㷨 aes, ��Կ����: 16, 24, 32byte
		string randkey = getRandStr(Len16);
		cout << "���ɵ������Կ��" << randkey << endl;
		// 2. ͨ����Կ����
		string  seckey = rsa.rsaPubKeyEncrypt(randkey);
		cout << "��Կ����֮�����Կ��" << seckey << endl;
		// 3. ��ʼ���ظ�������
		res_info.clientID = reqmsg->clientid();
		res_info.seckeyID = 12;//��Ҫ���ݿ����
		res_info.data = seckey;
		res_info.serverID = m_info.serverID;
		res_info.status = true;
	}
	// 4. ���л�
	CodecFactory* factory = new RespondFactory(&res_info);
	Codec* codec = factory->createCodec();
	string encstr = codec->encodeMsg();
	delete factory;
	delete codec;
	return encstr;
}
//Ҫ��: �ַ����а���: a-z, A-Z, 0-9, �����ַ�������ַ�����
string ServerOP::getRandStr(keylen len)
{
	srand(time(NULL));
	int flag = 0;
	string randstr = string();
	char* cs = "~!@#$%^&*()_+}{|\';[]";
	for (int i = 0; i < len; i++)
	{
		flag = rand() % 4;
		switch (flag)
		{
		case 0: //a~z
			randstr.append(1, 'a' + rand() % 26);
			break;
		case 1: //A~Z
			randstr.append(1, 'A' + rand() % 26);
			break;
		case 2: //0~9
			randstr.append(1, '0' + rand() % 10);
			break;
		case 3: //�����ַ�
			randstr.append(1, cs[rand() % strlen(cs)]);
			break;
		default:
			break;
		}
	}
	return randstr;
}
