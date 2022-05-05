#include <iostream>
#include "RequestFactory.h"
using namespace std;
//���캯����ʼ���б��Զ����ø��๹�캯�������Բ�д��,��ʼ���б�ʱҪ��˳���������룩
RequestFactory::RequestFactory(string encstr) :
	CodecFactory(), flag(false), m_encStr(encstr), m_info(NULL)
{}
//�б��ʼ��info�ṹ��
RequestFactory::RequestFactory(RequestInfo* info) :
	CodecFactory(), flag(true), m_encStr(""), m_info(info)
{}
//����ģʽ��������
Codec* RequestFactory::createCodec()
{
	Codec* codec = NULL;
	if (flag) {
		codec = new RequestCodec(m_info);
	}
	else
	{
		codec = new RequestCodec(m_encStr);
	}
	return codec;
}
//��������
RequestFactory::~RequestFactory(){}
