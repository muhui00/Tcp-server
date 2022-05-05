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
	//从配置文件读取数据初始化
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
	//创建TcpServer对象
	//设置监听
	m_server = new TcpServer;
	m_server->setListen(m_info.port);
	while (1)
	{
		// 等待并接受客户端连接请求, 默认连接超时时间为10000s
		TcpSocket* tcp_sock = m_server->acceptConnect();
		if (tcp_sock == NULL) {
			//连接失败
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
	// 通过参数将传递的this对象转换
	ServerOP* op = (ServerOP*)arg;
	//pthread_self(),获取线程本身的线程id
	TcpSocket* tcp = op->m_list[pthread_self()];
	
	//收到数据（数据反序列化解析）
	string msg = tcp->recvMsg();
	CodecFactory* factory = new RequestFactory(msg);
	Codec* codec = factory->createCodec();
	RequestMsg* req = (RequestMsg *)codec->decodeMsg();
	//根据cmdType判断客户端想要干什么
	switch (req->cmdtype())
	{
	case 1: //密钥协商
		data = op->keyAgreement(req);
		break;
	case 2: //密钥校验
		break;
	case 3: 
		break;
	default:
		break;
	}
	//释放资源
	delete factory;
	delete codec;
	//tcp对象处理
	tcp->sendMsg(data);
	tcp->disConnect();
	//删除
	op->m_list.erase(pthread_self());
	return NULL;
}

string ServerOP::keyAgreement(RequestMsg* reqmsg)
{
	// 0. 对签名进行校验 -> 公钥解密 -> 得到公钥
	// 将收到的公钥数据写入本地磁盘
	ofstream ofs("public.pem");
	ofs << reqmsg->data();
	ofs.close();
	RespondInfo res_info;
	// 创建非对称加密对象
	Cryptographic rsa("public.pem", false);
	// 创建哈希对象
	Hash hash(T_SHA1);
	hash.addData(reqmsg->data());
	//校检签名
	cout << "1111111111111111111111" << endl;
	bool b1 = rsa.rsaVerify(hash.result(), reqmsg->sign());
	cout << "0000000000000000000000" << endl;
	if (b1 == false) {
		cout << "签名校检失败..." << endl;
		res_info.status = false;
	}
	else
	{
		cout << "签名校验成功...." << endl;
		// 1. 生成随机字符串
		// 对称加密的秘钥, 使用对称加密算法 aes, 秘钥长度: 16, 24, 32byte
		string randkey = getRandStr(Len16);
		cout << "生成的随机密钥：" << randkey << endl;
		// 2. 通过公钥加密
		string  seckey = rsa.rsaPubKeyEncrypt(randkey);
		cout << "公钥加密之后的密钥：" << seckey << endl;
		// 3. 初始化回复的数据
		res_info.clientID = reqmsg->clientid();
		res_info.seckeyID = 12;//需要数据库操作
		res_info.data = seckey;
		res_info.serverID = m_info.serverID;
		res_info.status = true;
	}
	// 4. 序列化
	CodecFactory* factory = new RespondFactory(&res_info);
	Codec* codec = factory->createCodec();
	string encstr = codec->encodeMsg();
	delete factory;
	delete codec;
	return encstr;
}
//要求: 字符串中包含: a-z, A-Z, 0-9, 特殊字符（随机字符串）
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
		case 3: //特殊字符
			randstr.append(1, cs[rand() % strlen(cs)]);
			break;
		default:
			break;
		}
	}
	return randstr;
}
