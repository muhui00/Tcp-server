#pragma once
#include <string>
#include <openssl/aes.h>
using namespace std;

class AesCrypto
{
public:                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
	// ��ʹ�� 16byte, 24byte, 32byte ����Կ
	AesCrypto(string key);
	~AesCrypto();
	// ����
	string aesCBCEncrypt(string text);
	// ����
	string aesCBCDecrypt(string encStr);

private:
	//����ת��
	string Utf8ToGbk(const char* src_str);
	string aesCrypto(string data, int crypto);
	void generateIvec(unsigned char* ivec);
private:
	AES_KEY m_encKey;
	AES_KEY m_decKey;
	string m_key;	// ��Կ
};