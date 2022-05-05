#pragma once
#include <iostream>
#include "Codec.h"
using namespace std;

//工厂基类
class CodecFactory
{
public:
	CodecFactory();
	virtual Codec* createCodec();
	~CodecFactory();
};
