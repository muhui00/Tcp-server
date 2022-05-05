#pragma once
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <iostream>
using namespace std;

enum SignLevel
{
	Level1 = NID_md5,
	Level2 = NID_sha1,
	Level3 = NID_sha224,
	Level4 = NID_sha256,
	Level5 = NID_sha384,
	Level6 = NID_sha512
};

class Cryptographic {
public:
	Cryptographic();
	Cryptographic(string filename, bool isPrivate = true);
	~Cryptographic();

	// ����rsa��Կ��
	void generateRsaKey(int bits, string pub = "public.pem", string pri = "private.pem");
	// ��Կ����
	string encryptPublicKey(string data);
	// ˽Կ����
	string decryptPrivateKey(string encData);
	// ʹ��RSAǩ��
	string rsaSign(string data, SignLevel level = Level3);
	// ʹ��RSA��֤ǩ��
	bool rsaVerify(string data, string signData, SignLevel level = Level3);

private:
	// �õ���Կ
	bool initPublicKey(string pubfile);
	// �õ�˽Կ
	bool initPrivateKey(string prifile);

private:
	RSA* m_publicKey;  //��Կ
	RSA* m_privateKey; //˽Կ
};