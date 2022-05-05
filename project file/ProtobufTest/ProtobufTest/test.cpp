#include <iostream>
#include "person.pb.h"
using namespace std;
using namespace a;
int main() {
	Person p;
	p.set_id(1001);
	//申请一块内存
	p.add_name();
	p.set_name(0, "lufei");
	p.add_name();
	p.set_name(1, "lalsl");
	p.add_name();
	p.set_name(2, "fwefi");

	p.set_sex("man");
	p.set_age(17);
	//枚举
	p.set_color(Blue);
	b::Person* info = p.mutable_info();
	info->set_address("dasdasfds");
	info->set_number(911);

	string output;
	p.SerializeToString(&output);
	cout << "序列化后的数据：" << output << endl;

	Person pp;
	pp.ParseFromString(output);
	//ii是一个引用 将Info对象值取出来
	b::Person ii = pp.info();
	cout << "id:" << pp.id() << ", name:" 
		<< pp.name(0) << ", "
		<< pp.name(1) << ", "
		<< pp.name(2) 
		<< ",sex:" << pp.sex() << ",age:" << pp.age() 
		<< ", color"<< pp.color()
		<<", adress:"<<ii.address()
		<< ", number:" << ii.number()
		<< endl;
	system("pause");
	return 0;
}