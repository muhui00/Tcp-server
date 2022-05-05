#pragma once
#include <iostream>
#include "Codec.h"
#include "CodecFactory.h"
#include "RespondCodec.h"

class RespondFactory :
	public CodecFactory
{
public:
	RespondFactory(string encstr);
	RespondFactory(RespondInfo* info);
	Codec* createCodec();
	~RespondFactory();
private:
	bool m_flag;
	string m_encStr;
	RespondInfo* m_info;
};