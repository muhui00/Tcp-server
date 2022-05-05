#include <iostream>
#include "RequestFactory.h"
using namespace std;
//构造函数初始化列表，自动调用父类构造函数（可以不写）,初始化列表时要按顺序来（必须）
RequestFactory::RequestFactory(string encstr) :
	CodecFactory(), flag(false), m_encStr(encstr), m_info(NULL)
{}
//列表初始化info结构体
RequestFactory::RequestFactory(RequestInfo* info) :
	CodecFactory(), flag(true), m_encStr(""), m_info(info)
{}
//工厂模式创建对象
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
//析构函数
RequestFactory::~RequestFactory(){}
