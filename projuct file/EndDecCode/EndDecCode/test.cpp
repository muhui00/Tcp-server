#include "Codec.h"
#include "RequestCodec.h"
#include "RespondCodec.h"
#include "CodecFactory.h"
#include "RequestFactory.h"
#include "RespondFactory.h"
#include <iostream>
using namespace std;
//多态的使用：1、有继承关系； 2、父类中有虚函数； 3、子类中重写父类中的虚函数； 4、父类指针指向子类对象

//编码
string encodeMsg(Codec* codec) {
	return codec->encodeMsg();
}

//解码
void* decodeMsg(Codec* codec) {
	return codec->decodeMsg();
}
int main() {
	////初始化数据
	//RequestInfo info;
	//info.cmd = 9;
	//info.clientID = "onePiece";
	//info.serverID = "lufei";
	//info.data = "努力努力";
	//info.sign = "哈哈哈哈";
	////创建子类对象
	//RequestCodec req(&info);
	////编码
	//string reqmsg = encodeMsg(&req);
	//
	////解码
	//RequestCodec req1(reqmsg);
	//RequestMsg* resMsg = (RequestMsg *)decodeMsg(&req1);
	//cout << "cmdtype: " << resMsg->cmdtype()
	//	<< ", clinetID: " << resMsg->clientid()
	//	<< ", serverID: " << resMsg->serverid()
	//	<< ", sign: " << resMsg->sign()
	//	<< ", data: " << resMsg->data() << endl;
	//cout << "==========================" << endl;
	//RespondInfo Info;
	//Info.status = false;
	//Info.seckeyID = 10;
	//Info.clientID = "a";
	//Info.serverID = "a";
	//Info.data = "a";
	////编码
	////创建子类对象 调用构造函数
	//RespondCodec rsd(&Info);
	////rsd.encodeMsg();
	////父类指针codec指向子类对象rsd，调用子类重写的函数（继承关系）
	//string str = encodeMsg(&rsd);
	////解码
	//RespondCodec rsq1(str);
	//RespondMsg* rsdmsg = (RespondMsg*)decodeMsg(&rsq1);
	//cout << "status: " << rsdmsg->status()
	//	<< ", clinetID: " << rsdmsg->clientid()
	//	<< ", serverID: " << rsdmsg->serverid()
	//	<< ", secky: " << rsdmsg->seckeyid()
	//	<< ", data: " << rsdmsg->data() << endl;
	//cout << "==========================" << endl;
	

	//初始化结构体数据
	RequestInfo req_info = { 1,"qgdueq", "dadade", "pyugyed","dwawjbc" };
	//工厂模式创建对象
	CodecFactory* factory = NULL;

	Codec* codec = NULL;
	//编码
	//调用构造函数创建对象
	factory = new RequestFactory(&req_info);
	codec = factory->createCodec();
	//调用编码函数
	string str = codec->encodeMsg();
	//输出编码后的字符串
	cout << "序列化数据：" << str << endl;
	//释放堆区内存
	delete factory;
	delete codec;

	//解码
	factory = new RequestFactory(str);
	codec = factory->createCodec();
	//调用解码函数
	RequestMsg *req = (RequestMsg *)codec->decodeMsg();
	//输出解码后的数据
	cout << "cmdtype:" << req->cmdtype()
		<< ",clientid:" << req->clientid()
		<< ",serverid" << req->serverid()
		<< ",data:" << req->data()
		<< ",sign:" << req->sign() << endl;


	system("pause");
	return 0;
}