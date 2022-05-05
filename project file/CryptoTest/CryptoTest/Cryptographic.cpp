#include "Cryptographic.h"
#include <openssl/bio.h>
#include <openssl/err.h>
#include <iostream>
extern "C"
{
#include <openssl/applink.c>
};

Cryptographic::Cryptographic() :
	m_publicKey(RSA_new()),m_privateKey(RSA_new())
{}
Cryptographic::Cryptographic(string filename, bool isPrivate) 
{

}

Cryptographic::~Cryptographic() 
{

}

// 生成rsa密钥对
void Cryptographic::generateRsaKey(int bits, string pub, string pri)
{
	// 1. 创建rsa变量
	RSA* rsa = RSA_new();
	// 1.5 创建bignum对象, 并初始化
	BIGNUM* e = BN_new();
	BN_set_word(e, bits);
	// 2. 生成密钥对 -> 密钥对在内存中
	RSA_generate_key_ex(rsa, 1024, e, NULL);
	// 3. 将密钥对写入到磁盘
	BIO* bio = BIO_new_file(pub.data(), "w");
	PEM_write_bio_RSAPublicKey(bio, rsa);
	// 释放资源
	BIO_free(bio);
	bio = BIO_new_file(pri.data(), "w");
	PEM_write_bio_RSAPrivateKey(bio, rsa, NULL, NULL, 0, NULL, NULL);
	BIO_free(bio);

	//(从内存)得到公钥私钥
	m_privateKey = RSAPrivateKey_dup(rsa);
	m_publicKey = RSAPublicKey_dup(rsa);

	BN_free(e);
	RSA_free(rsa);

}

// 得到公钥
bool Cryptographic::initPublicKey(string pubfile)
{
	// 通过BIO读文件
	BIO* pubBio = BIO_new_file(pubfile.data(), "r");
	// 将bio中的pem数据读出
	if (PEM_read_bio_RSAPublicKey(pubBio, &m_publicKey, NULL, NULL) == NULL)
	{
		ERR_print_errors_fp(stdout);
		return false;
	}
	BIO_free(pubBio);
	return true;
}
// 得到私钥
bool Cryptographic::initPrivateKey(string prifile)
{
	// 通过bio读文件
	BIO* priBio = BIO_new_file(prifile.data(), "r");
	// 将bio中的pem数据读出
	if (PEM_read_bio_RSAPrivateKey(priBio, &m_privateKey, NULL, NULL) == NULL)
	{
		ERR_print_errors_fp(stdout);
		return false;
	}
	BIO_free(priBio);
	return true;
}
// 公钥加密
string Cryptographic::encryptPublicKey(string data)
{
	//计算公钥长度
	int keyLen = RSA_size(m_publicKey);
	char* buf = new char[keyLen + 1];
	// 返回值就是密文长度
	int ret = RSA_public_encrypt(data.size(), (const unsigned char*)data.data(),
		(unsigned char*)buf, m_publicKey, RSA_PKCS1_PADDING);
	string retstr = string();
	if (ret > 0) {
		//加密成功
		retstr = string(buf, keyLen);
	}
	delete[] buf;
	return retstr;

}
// 私钥解密
string Cryptographic::decryptPrivateKey(string encData)
{
	// 解密 -> 明文
	// 数据被加密之后, 长度和秘钥长度相同
	// 通过函数计算秘钥长度
	int keyLen = RSA_size(m_privateKey);
	char* buf = new char[keyLen];
	// 返回值是解密之后的数据长度 == 原始数据长度
	int len = RSA_private_decrypt(encData.size(), (const unsigned char*)encData.data(),
		(unsigned char*)buf, m_privateKey, RSA_PKCS1_PADDING);
	string retstr = string();
	if (len >= 0) {
		//解密成功
		retstr = string(buf, keyLen);
	}
	delete[] buf;
	return retstr;

}
// 使用RSA签名
string Cryptographic::rsaSign(string data, SignLevel level)
{
	int len = RSA_size(m_privateKey);
	unsigned int outLen = 0;
	char* out = new char[len];
	RSA_sign(level, (const unsigned char*)data.data(), data.size(),
		(unsigned char*)out, &outLen, m_privateKey);
	cout << "sign len: " << len << endl;
	string retStr = string(out, outLen);
	delete[] out;
	return retStr;
}
// 使用RSA验证签名
bool Cryptographic::rsaVerify(string data, string signData, SignLevel level)
{
	// 验证签名
	int ret = RSA_verify(level, (const unsigned char*)data.data(), data.size(),
		(const unsigned char*)signData.data(), signData.size(), m_publicKey);
	if (ret != 1)
	{
		return false;
	}
	return true;
}
