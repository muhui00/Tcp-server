#pragma once
#include "Codec.h"
#include "massage.pb.h"
#include <iostream>
using namespace std;

struct RespondInfo
{
	bool status;
	int seckeyID;
	string clientID;
	string serverID;
	string data;

};

class RespondCodec:
	public Codec
{
public:
	RespondCodec();
	RespondCodec(string encstr);
	RespondCodec(RespondInfo* info);
	void initMessage(string encstr);
	void initMessage(RespondInfo* info);
	string encodeMsg();
	void* decodeMsg();
	~RespondCodec();
private:
	string m_encStr;
	RespondMsg m_msg;
};