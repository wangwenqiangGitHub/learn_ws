#include <vector>
#include <iostream>
#include <stdio.h>
/*
**vector 24 byte 
*/
int main(int argc, char** argv)
{
	std::vector<int> a;
	std::vector<double> b;
	printf("vector %ld\ndouble %ld\n", sizeof(a),sizeof(b));
	return 0;
}
