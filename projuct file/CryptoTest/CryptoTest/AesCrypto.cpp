#include "AesCrypto.h"
#include <openssl/aes.h>
#include <Windows.h>
#include <string.h>
#include <iostream>
using namespace std;
// 可使用 16byte, 24byte, 32byte 的秘钥
AesCrypto::AesCrypto(string key)
{
	if (key.size() == 16 || key.size() == 24 || key.size() == 32) {
		AES_set_encrypt_key((const unsigned char*)key.data(), key.size() * 8, &m_encKey);
		AES_set_decrypt_key((const unsigned char*)key.data(), key.size() * 8, &m_decKey);
		m_key = key;
	}
}
AesCrypto::~AesCrypto()
{}
// 加密
string AesCrypto::aesCBCEncrypt(string text)
{
	return aesCrypto(text, AES_ENCRYPT);
}
// 解密
string AesCrypto::aesCBCDecrypt(string encStr)
{
	return aesCrypto(encStr, AES_DECRYPT);
}

string AesCrypto::Utf8ToGbk(const char* src_str)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, src_str, -1, NULL, 0);
	wchar_t* wszGBK = new wchar_t[len + 1];
	memset(wszGBK, 0, len * 2 + 2);
	MultiByteToWideChar(CP_UTF8, 0, src_str, -1, wszGBK, len);
	len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
	char* szGBK = new char[len + 1];
	memset(szGBK, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGBK, len, NULL, NULL);
	string strTemp(szGBK);
	if (wszGBK) delete[] wszGBK;
	if (szGBK) delete[] szGBK;
	return strTemp;
}
string AesCrypto::aesCrypto(string data, int crypto)
{
	AES_KEY* key = crypto == AES_ENCRYPT ? &m_encKey : &m_decKey;
	//加密
	//计算长度
	int len = strlen(data.data()) + 1;
	int length = 0;
	if (len % 16 != 0) {
		length = (len / 16 + 1) * 16;
	}
	else
	{
		length = len;
	}
	char* out = new char[length];
	unsigned char ivec[AES_BLOCK_SIZE];
	generateIvec(ivec);
	AES_cbc_encrypt((const unsigned char*)data.data(), (unsigned char*)out, length, key, ivec, crypto);
	//cout << "out:" << out << endl;
	//int outlen = strlen(out);
	string str;
	if (crypto == AES_DECRYPT) {
		str = Utf8ToGbk(out);
	}
	
	str = string(out);
	delete[] out;
	return str;
}
void AesCrypto::generateIvec(unsigned char* ivec)
{
	for (int i = 0; i < AES_BLOCK_SIZE; ++i)
	{
		ivec[i] = m_key.at(AES_BLOCK_SIZE - i - 1);
	}
}