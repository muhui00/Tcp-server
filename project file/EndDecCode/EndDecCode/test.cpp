#include "Codec.h"
#include "RequestCodec.h"
#include "RespondCodec.h"
#include "CodecFactory.h"
#include "RequestFactory.h"
#include "RespondFactory.h"
#include <iostream>
using namespace std;
//��̬��ʹ�ã�1���м̳й�ϵ�� 2�����������麯���� 3����������д�����е��麯���� 4������ָ��ָ���������

//����
string encodeMsg(Codec* codec) {
	return codec->encodeMsg();
}

//����
void* decodeMsg(Codec* codec) {
	return codec->decodeMsg();
}
int main() {
	////��ʼ������
	//RequestInfo info;
	//info.cmd = 9;
	//info.clientID = "onePiece";
	//info.serverID = "lufei";
	//info.data = "Ŭ��Ŭ��";
	//info.sign = "��������";
	////�����������
	//RequestCodec req(&info);
	////����
	//string reqmsg = encodeMsg(&req);
	//
	////����
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
	////����
	////����������� ���ù��캯��
	//RespondCodec rsd(&Info);
	////rsd.encodeMsg();
	////����ָ��codecָ���������rsd������������д�ĺ������̳й�ϵ��
	//string str = encodeMsg(&rsd);
	////����
	//RespondCodec rsq1(str);
	//RespondMsg* rsdmsg = (RespondMsg*)decodeMsg(&rsq1);
	//cout << "status: " << rsdmsg->status()
	//	<< ", clinetID: " << rsdmsg->clientid()
	//	<< ", serverID: " << rsdmsg->serverid()
	//	<< ", secky: " << rsdmsg->seckeyid()
	//	<< ", data: " << rsdmsg->data() << endl;
	//cout << "==========================" << endl;
	

	//��ʼ���ṹ������
	RequestInfo req_info = { 1,"qgdueq", "dadade", "pyugyed","dwawjbc" };
	//����ģʽ��������
	CodecFactory* factory = NULL;

	Codec* codec = NULL;
	//����
	//���ù��캯����������
	factory = new RequestFactory(&req_info);
	codec = factory->createCodec();
	//���ñ��뺯��
	string str = codec->encodeMsg();
	//����������ַ���
	cout << "���л����ݣ�" << str << endl;
	//�ͷŶ����ڴ�
	delete factory;
	delete codec;

	//����
	factory = new RequestFactory(str);
	codec = factory->createCodec();
	//���ý��뺯��
	RequestMsg *req = (RequestMsg *)codec->decodeMsg();
	//�������������
	cout << "cmdtype:" << req->cmdtype()
		<< ",clientid:" << req->clientid()
		<< ",serverid" << req->serverid()
		<< ",data:" << req->data()
		<< ",sign:" << req->sign() << endl;


	system("pause");
	return 0;
}