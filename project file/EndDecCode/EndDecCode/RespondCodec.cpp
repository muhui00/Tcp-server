#include "RespondCodec.h"
#include <iostream>

RespondCodec::RespondCodec() {

}

RespondCodec::RespondCodec(string encstr) {
	initMessage(encstr);
}

RespondCodec::RespondCodec(RespondInfo* info) {
	initMessage(info);
}

void RespondCodec::initMessage(string encstr) {
	m_encStr = encstr;
}

void RespondCodec::initMessage(RespondInfo* info) {
	m_msg.set_status(info->status);
	m_msg.set_seckeyid(info->seckeyID);
	m_msg.set_clientid(info->clientID);
	m_msg.set_serverid(info->serverID);
	m_msg.set_data(info->data);
}

string RespondCodec::encodeMsg() {
	string output;
	m_msg.SerializeToString(&output);
	return output;
}

void* RespondCodec::decodeMsg() {
	m_msg.ParseFromString(m_encStr);
	return &m_msg;
}

RespondCodec::~RespondCodec() {

}