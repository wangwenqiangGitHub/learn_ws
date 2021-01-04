#include"sub_1.h"					//预处理
void main(){
	float x,y;
	float a=12,b=13;				//a=12,b=13
	x=sumfloat(a,b);				//x=a+b
	y=subfloat(a,b);				//y=a-b
	printf("%f+%f=%f\n",a,b,x);		//打印浮点相加的值
	printf("%f-%f=%f\n",a,b,y);		//打印浮点相减的值
}