#include <stdio.h>

/**
大端存储：就是把一个数的低位字节序的内容放在高地址处，高位字节序的内容存放在低地址处。
小端存储：就是把一个数的低位字节序的内容放到低地址处，高位字节序的内容存放在高地址处
int a = 1;
内存中存储应该是0x00 00 00 01 , 为什么编译器给出的却是0x 01 00 00 00  
因为计算机存储是小端存储
**/

//利用共同体（联合union）来检测

int Check_sys()
{
    union Un
    {
        char c;
        int i;
    }un;
    un.i = 1;
    return un.c;
}
#if 0 
int Check_sys()
{
    int a = 1;
    //char* p = (char*)&a;
    //return *p;  //大端返回0，小端返回1
    //还可以写成下面的方式：
    return *(char*)&a;
}
#endif
int main()
{
    int ret=Check_sys();   
    if (1 == ret)
    {
        printf("当前模式为小端存储\n");
    }
    else
    {
        printf("当前模式为大端存储\n");
    }
    return 0;
}
