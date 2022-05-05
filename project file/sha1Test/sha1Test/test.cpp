#include <iostream>
#include <string.h>
#include <assert.h>
#include <openssl/sha.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/aes.h>
extern "C"
{
#include <openssl/applink.c> // �����ʱ��applinc.c������ȥ�������
};
using namespace std;
#include <windows.h>

void sha1test()
{
	SHA_CTX ctx;
	SHA1_Init(&ctx);
	SHA1_Update(&ctx, "hello", strlen("hello"));
	SHA1_Update(&ctx, ",world", strlen(",world"));
	unsigned char *md = new unsigned char[SHA_DIGEST_LENGTH];
	char *res = new char[SHA_DIGEST_LENGTH * 2 + 1];
	SHA1_Final(md, &ctx);
	//��ʽת��
	for (int i = 0; i < SHA_DIGEST_LENGTH; ++i)
	{
		sprintf(&res[i * 2], "%02x", md[i]);
	}
	cout << "sha1:" << res << endl;
}
void generateRsaKey()
{
	// 1������rsa����
	RSA *rsa = RSA_new();
	// 1.5������bignum���󣬲���ʼ��
	BIGNUM *e = BN_new();
	BN_set_word(e, 12345);
	// 2��������Կ�ԣ��洢���ڴ���
	RSA_generate_key_ex(rsa, 2048, e, NULL);

	//����Կд�뵽����
	// 1������bio����
	BIO *bio = BIO_new_file("public.pem", "w");
	PEM_write_bio_RSAPublicKey(bio, rsa);
	BIO_free(bio);
	bio = BIO_new_file("private.pem", "w");
	PEM_write_bio_RSAPrivateKey(bio, rsa, NULL, NULL, 0, NULL, NULL);
	BIO_free(bio);
}
//��Կ����
string encryptPublicKey()
{
	//׼��Ҫ���ܵ�����
	string data = "���ͣ�Ŭ�������ܷ���!";
	//��ȡ׼����Կ
	BIO *bio = BIO_new_file("public.pem", "r");
	//����RSA����
	RSA *publicKey = RSA_new();
	if (PEM_read_bio_RSAPublicKey(bio, &publicKey, NULL, NULL) == NULL)
	{
		cout << "��Կ��ȡʧ�ܣ�" << endl;
		return string();
	}
	//�ͷ���Դ
	BIO_free(bio);
	//����
	//���ݱ�����֮�󣬳�������Կ������ͬ
	//ͨ������������Կ����
	int keylen = RSA_size(publicKey);
	//��̬������ַ���ָ��
	char *buf = new char[keylen];
	int len = RSA_public_encrypt(data.size(), (const unsigned char *)data.data(),
								 (unsigned char *)buf, publicKey, RSA_PKCS1_PADDING);
	//�����ķ���
	cout << "���ĳ��ȣ�" << len << endl;
	cout << "buf:" << buf << endl;
	return string(buf, len);
}
//˽Կ����
string decryptPrivateKey(string str)
{
	//��ȡ˽Կ
	BIO *bio = BIO_new_file("private.pem", "r");
	//׼��RSA����
	RSA *privtatKey = RSA_new();
	if (PEM_read_bio_RSAPrivateKey(bio, &privtatKey, NULL, NULL) == NULL)
	{
		cout << "˽Կ��ȡʧ��" << endl;
		return string();
	}
	//�ͷ���Դ
	BIO_free(bio);
	//����
	//������Կ����
	int keylen = RSA_size(privtatKey);
	//׼��ָ��ռ�
	char *buf = new char[keylen];
	int len = RSA_private_decrypt(str.size(), (const unsigned char *)str.data(), (unsigned char *)buf,
								  privtatKey, RSA_PKCS1_PADDING);
	cout << "buf: " << buf << endl;
	return string(buf, len);
}
// ǩ������֤ǩ��
void rsaSigAndVerfiy()
{
	// 1��ǩ������
	string data = "����������ǿ��";
	// 2����ȡ��Կ
	RSA *pubKey = RSA_new();
	RSA *priKey = RSA_new();
	//��ȡ��Կ
	BIO *bio = BIO_new_file("public.pem", "r");
	if (PEM_read_bio_RSAPublicKey(bio, &pubKey, NULL, NULL) == NULL)
	{
		cout << "��Կ��ȡʧ��" << endl;
	}
	BIO_free(bio);
	//��ȡ˽Կ
	bio = BIO_new_file("private.pem", "r");
	if (PEM_read_bio_RSAPrivateKey(bio, &priKey, NULL, NULL) == NULL)
	{
		cout << "˽Կ��ȡʧ��" << endl;
	}
	BIO_free(bio);
	// 3��ǩ��
	int keylen = RSA_size(priKey);
	unsigned int siglen = 0;
	unsigned char *sigret = new unsigned char[keylen];
	RSA_sign(NID_sha1, (const unsigned char *)data.data(), (unsigned int)data.size(), sigret, &siglen, priKey);
	string sigbuf((char *)sigret, keylen);
	// 4����֤
	int ret = RSA_verify(NID_sha1, (const unsigned char *)data.data(), (unsigned int)data.size(),
						 (const unsigned char *)sigbuf.data(), (unsigned int)sigbuf.size(), pubKey);
	cout << "ret=" << ret << endl;
}
string Utf8ToGbk(const char* src_str)
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
void aescryto() {
	//准备数据
	const char* test = "才能金额v和iwf而覅火车去地球回去后我发你为大家旗舰店取得进球哦i都i额度就哦i恶化耦合iwe哦i我欸为哦哦i恶化二号iohhehvowowjowjdiwj短期的hi强化其核心七fvewfvev点hi强化";
	//初始化秘钥格式 AES_KEY
	const char* key = "1234567887654321";
	/*int l = strlen(tdata);
	char* key = new char[l * 2 + 1];
	for (int i = 0; i < l; ++i)
	{
		sprintf(&key[i * 2], "%02x", tdata[i]);
	}*/
	//加密密钥
	AES_KEY enckey;
	AES_set_encrypt_key((const unsigned char*)key, 128, &enckey);
	//加密
	//计算长度
	int len = strlen(test) + 1;
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
	memset(&ivec, 9, sizeof(ivec));
	AES_cbc_encrypt((const unsigned char*)test, (unsigned char*)out, length, &enckey, ivec, AES_ENCRYPT);
	//cout << out << endl;

	//解密
	AES_KEY deckey;
	AES_set_decrypt_key((const unsigned char*)key, 128, &deckey);
	char* data = new char[length];
	memset(&ivec, 9, sizeof(ivec));
	AES_cbc_encrypt((const unsigned char*)out, (unsigned char*)data, length, &deckey, ivec, AES_DECRYPT);
	//返回
	cout << data << endl;
	string str = Utf8ToGbk(data);
	cout << str << endl;
	
	delete[] out;
	delete[] data;
}
int main()
{
	// sha1test();
	////generateRsaKey();
	// string str = encryptPublicKey();
	// string str2 = decryptPrivateKey(str);
	// cout << "���ܺ�����ݣ�" << str2 << endl;
	//rsaSigAndVerfiy();
	aescryto();
	system("pause");
	return 0;
}