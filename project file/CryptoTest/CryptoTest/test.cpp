#include "AesCrypto.h"
#include <iostream>
#include <string.h>
using namespace std;
int main()
{
	//准备加密数据及密钥
	string encstr = "AES是一套对称密钥的密码术，目前已广泛使用，用于替代已经不够安全的DES算法AES是一套对称密钥的密码术，目前已广泛使用，用于替代已经不够安全的DES算法AES是一套对称密钥的密码术，目前已广泛使用，用于替代已经不够安全的DES算法AES是一套对称密钥的密码术，目前已广泛使用，用于替代已经不够安全的DES算法AES是一套对称密钥的密码术，目前已广泛使用，用于替代已经不够安全的DES算法AES是一套对称密钥的密码术，目前已广泛使用，用于替代已经不够安全的DES算法";
	string key = "1234567887654321";
	//创建AES加密对象
	AesCrypto encry(key);

	//加密
	string str = encry.aesCBCEncrypt(encstr);
	//解密
	string str1 = encry.aesCBCDecrypt(str);
	cout << str1 << endl;
	system("pause");
	return 0;
}