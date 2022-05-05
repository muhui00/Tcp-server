#pragma once
#include <iostream>
#include "CodecFactory.h"
#include "RequestCodec.h"

class RequestFactory :
	public CodecFactory
{
public:
	RequestFactory(string encstr);
	RequestFactory(RequestInfo* info);
	Codec* createCodec();
	~RequestFactory();

private:
	bool flag;
	string m_encStr;
	RequestInfo* m_info;
};