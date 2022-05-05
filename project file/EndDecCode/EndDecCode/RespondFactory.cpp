#include "RespondFactory.h"
//���캯����ʼ���б�
RespondFactory::RespondFactory(string encstr) :
	m_flag(true), m_encStr(encstr), m_info(NULL)
{}

RespondFactory::RespondFactory(RespondInfo* info) :
	m_flag(false), m_encStr(""), m_info(info)
{}

Codec* RespondFactory::createCodec()
{
	Codec* codec = NULL;
	if (m_flag) {
		codec = new RespondCodec(m_encStr);
	}
	else
	{
		codec = new RespondCodec(m_info);
	}
	return codec;
}