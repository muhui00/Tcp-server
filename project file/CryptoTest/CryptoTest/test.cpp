#include "AesCrypto.h"
#include <iostream>
#include <string.h>
using namespace std;
int main()
{
	//׼���������ݼ���Կ
	string encstr = "AES��һ�׶Գ���Կ����������Ŀǰ�ѹ㷺ʹ�ã���������Ѿ�������ȫ��DES�㷨AES��һ�׶Գ���Կ����������Ŀǰ�ѹ㷺ʹ�ã���������Ѿ�������ȫ��DES�㷨AES��һ�׶Գ���Կ����������Ŀǰ�ѹ㷺ʹ�ã���������Ѿ�������ȫ��DES�㷨AES��һ�׶Գ���Կ����������Ŀǰ�ѹ㷺ʹ�ã���������Ѿ�������ȫ��DES�㷨AES��һ�׶Գ���Կ����������Ŀǰ�ѹ㷺ʹ�ã���������Ѿ�������ȫ��DES�㷨AES��һ�׶Գ���Կ����������Ŀǰ�ѹ㷺ʹ�ã���������Ѿ�������ȫ��DES�㷨";
	string key = "1234567887654321";
	//����AES���ܶ���
	AesCrypto encry(key);

	//����
	string str = encry.aesCBCEncrypt(encstr);
	//����
	string str1 = encry.aesCBCDecrypt(str);
	cout << str1 << endl;
	system("pause");
	return 0;
}