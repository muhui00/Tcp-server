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

// ����rsa��Կ��
void Cryptographic::generateRsaKey(int bits, string pub, string pri)
{
	// 1. ����rsa����
	RSA* rsa = RSA_new();
	// 1.5 ����bignum����, ����ʼ��
	BIGNUM* e = BN_new();
	BN_set_word(e, bits);
	// 2. ������Կ�� -> ��Կ�����ڴ���
	RSA_generate_key_ex(rsa, 1024, e, NULL);
	// 3. ����Կ��д�뵽����
	BIO* bio = BIO_new_file(pub.data(), "w");
	PEM_write_bio_RSAPublicKey(bio, rsa);
	// �ͷ���Դ
	BIO_free(bio);
	bio = BIO_new_file(pri.data(), "w");
	PEM_write_bio_RSAPrivateKey(bio, rsa, NULL, NULL, 0, NULL, NULL);
	BIO_free(bio);

	//(���ڴ�)�õ���Կ˽Կ
	m_privateKey = RSAPrivateKey_dup(rsa);
	m_publicKey = RSAPublicKey_dup(rsa);

	BN_free(e);
	RSA_free(rsa);

}

// �õ���Կ
bool Cryptographic::initPublicKey(string pubfile)
{
	// ͨ��BIO���ļ�
	BIO* pubBio = BIO_new_file(pubfile.data(), "r");
	// ��bio�е�pem���ݶ���
	if (PEM_read_bio_RSAPublicKey(pubBio, &m_publicKey, NULL, NULL) == NULL)
	{
		ERR_print_errors_fp(stdout);
		return false;
	}
	BIO_free(pubBio);
	return true;
}
// �õ�˽Կ
bool Cryptographic::initPrivateKey(string prifile)
{
	// ͨ��bio���ļ�
	BIO* priBio = BIO_new_file(prifile.data(), "r");
	// ��bio�е�pem���ݶ���
	if (PEM_read_bio_RSAPrivateKey(priBio, &m_privateKey, NULL, NULL) == NULL)
	{
		ERR_print_errors_fp(stdout);
		return false;
	}
	BIO_free(priBio);
	return true;
}
// ��Կ����
string Cryptographic::encryptPublicKey(string data)
{
	//���㹫Կ����
	int keyLen = RSA_size(m_publicKey);
	char* buf = new char[keyLen + 1];
	// ����ֵ�������ĳ���
	int ret = RSA_public_encrypt(data.size(), (const unsigned char*)data.data(),
		(unsigned char*)buf, m_publicKey, RSA_PKCS1_PADDING);
	string retstr = string();
	if (ret > 0) {
		//���ܳɹ�
		retstr = string(buf, keyLen);
	}
	delete[] buf;
	return retstr;

}
// ˽Կ����
string Cryptographic::decryptPrivateKey(string encData)
{
	// ���� -> ����
	// ���ݱ�����֮��, ���Ⱥ���Կ������ͬ
	// ͨ������������Կ����
	int keyLen = RSA_size(m_privateKey);
	char* buf = new char[keyLen];
	// ����ֵ�ǽ���֮������ݳ��� == ԭʼ���ݳ���
	int len = RSA_private_decrypt(encData.size(), (const unsigned char*)encData.data(),
		(unsigned char*)buf, m_privateKey, RSA_PKCS1_PADDING);
	string retstr = string();
	if (len >= 0) {
		//���ܳɹ�
		retstr = string(buf, keyLen);
	}
	delete[] buf;
	return retstr;

}
// ʹ��RSAǩ��
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
// ʹ��RSA��֤ǩ��
bool Cryptographic::rsaVerify(string data, string signData, SignLevel level)
{
	// ��֤ǩ��
	int ret = RSA_verify(level, (const unsigned char*)data.data(), data.size(),
		(const unsigned char*)signData.data(), signData.size(), m_publicKey);
	if (ret != 1)
	{
		return false;
	}
	return true;
}
