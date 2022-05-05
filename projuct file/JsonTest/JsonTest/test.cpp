#include <json/json.h>
#include <iostream>
#include <fstream>
using namespace std;
using namespace Json;
void writeJson()
{
	// 组织数据, 并写入到磁盘文件
	// [12, 19.8, true, "hello", ["a", "b", "c"], {"name":"xiaoming"}, "age":12]
	//创建json对象
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
	// 将得到Value对象 v 格式化 -> string -> 写磁盘
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
			// 继续遍历这个子数组
			for (int j = 0; j < sub.size(); ++j)
			{
				cout << sub[j].asString() << " ";
			}
			cout << endl;
		}
		else if (sub.isObject())
		{
			// 根据对象中的key, 打印value值
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