#pragma once
#include <iostream>
#include "Codec.h"
using namespace std;

//��������
class CodecFactory
{
public:
	CodecFactory();
	virtual Codec* createCodec();
	~CodecFactory();
};
