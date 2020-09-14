#include <iostream>

class baseA
{
public:
virtual void print(){std::cout<< "hello baseA"<<std::endl;}
virtual void hi(){ print(); std::cout<<"hi a"<<std::endl;}
void test ();
};

void baseA::test()
{
	print();
}


class B:public baseA
{
public:
void print(){std::cout<< "hello B"<<std::endl;}
void my_b();
};

void B::my_b()
{
	hi();
}


int main()
{

	baseA aa;
	B bb;

	aa.test();
	bb.my_b();
	return 0;
}
