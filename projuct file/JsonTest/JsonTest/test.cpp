#include <json/json.h>
#include <iostream>
#include <fstream>
using namespace std;
using namespace Json;
void writeJson()
{
	// ��֯����, ��д�뵽�����ļ�
	// [12, 19.8, true, "hello", ["a", "b", "c"], {"name":"xiaoming"}, "age":12]
	//����json����
	Value root;
	root.append(12);
	root.append(19.8);
	root.append(true);
	root.append("hello");
	Value arr;
	arr.append("a");
	arr.append("b");
	arr.append("c");
	root.append(arr);
	Value obj;
	obj["name"] = "xiaoming";
	obj["age"] = 12;
	root.append(obj);
	// ���õ�Value���� v ��ʽ�� -> string -> д����
	FastWriter f;
	string str = f.write(root);
	cout << str << endl;
	ofstream ofs("test.json");
	ofs << str;
	ofs.close();

}

void readJson()
{
	ifstream ifs("test.json");
	Reader rd;
	Value root;
	rd.parse(ifs, root);
	for (int i = 0; i < root.size(); i++) {
		Value sub = root[i];
		if (sub.isInt())
		{
			cout << sub.asInt() << " ";
		}
		else if (sub.isDouble())
		{
			cout << sub.asDouble() << " ";
		}
		else if (sub.isBool())
		{
			cout << sub.asBool() << " ";
		}
		else if (sub.isString())
		{
			cout << sub.asString() << " ";
		}
		else if (sub.isArray())
		{
			// �����������������
			for (int j = 0; j < sub.size(); ++j)
			{
				cout << sub[j].asString() << " ";
			}
			cout << endl;
		}
		else if (sub.isObject())
		{
			// ���ݶ����е�key, ��ӡvalueֵ
			cout << sub["name"].asString() << ", "
				<< sub["age"].asInt() << " ";
		}
	}
}
int main() {
	writeJson();
	readJson();
	return 0;
}